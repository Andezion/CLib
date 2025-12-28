#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "../nn/dropout.h"
#include "../nn/batchnorm.h"
#include "array/array.h"

int main(void)
{
    srand(time(NULL));

    const size_t in_dim = 4;
    const size_t h1 = 128;
    const size_t h2 = 64;
    const size_t h3 = 32;
    const size_t h4 = 16;
    const size_t out_dim = 3;

    struct dense_layer *l1 = dense_create(in_dim, h1);
    struct dense_layer *l2 = dense_create(h1, h2);
    struct dense_layer *l3 = dense_create(h2, h3);
    struct dense_layer *l4 = dense_create(h3, h4);
    struct dense_layer *l5 = dense_create(h4, out_dim);

    struct batchnorm_layer *bn1 = batchnorm_create(h1);
    struct batchnorm_layer *bn2 = batchnorm_create(h2);
    struct batchnorm_layer *bn3 = batchnorm_create(h3);
    struct batchnorm_layer *bn4 = batchnorm_create(h4);

    if (!l1 || !l2 || !l3 || !l4 || !l5 || !bn1 || !bn2 || !bn3 || !bn4)
    {
        printf("failed to create layers\n");
        return 1;
    }

    const double xav1 = sqrt(6.0 / (l1->in_dim + l1->out_dim));
    const double xav2 = sqrt(6.0 / (l2->in_dim + l2->out_dim));
    const double xav3 = sqrt(6.0 / (l3->in_dim + l3->out_dim));
    const double xav4 = sqrt(6.0 / (l4->in_dim + l4->out_dim));
    const double xav5 = sqrt(6.0 / (l5->in_dim + l5->out_dim));

    for (size_t i = 0; i < l1->W->rows; i++)
    {
        for (size_t j = 0; j < l1->W->cols; j++)
        {
            l1->W->data[i][j] = ((float64_t)rand() / RAND_MAX * 2.0 - 1.0) * xav1;
        }
    }

    for (size_t i = 0; i < l2->W->rows; i++)
    {
        for (size_t j = 0; j < l2->W->cols; j++)
        {
            l2->W->data[i][j] = ((float64_t)rand() / RAND_MAX * 2.0 - 1.0) * xav2;
        }
    }

    for (size_t i = 0; i < l3->W->rows; i++)
    {
        for (size_t j = 0; j < l3->W->cols; j++)
        {
            l3->W->data[i][j] = ((float64_t)rand() / RAND_MAX * 2.0 - 1.0) * xav3;
        }
    }

    for (size_t i = 0; i < l4->W->rows; i++)
    {
        for (size_t j = 0; j < l4->W->cols; j++)
        {
            l4->W->data[i][j] = ((float64_t)rand() / RAND_MAX * 2.0 - 1.0) * xav4;
        }
    }

    for (size_t i = 0; i < l5->W->rows; i++)
    {
        for (size_t j = 0; j < l5->W->cols; j++)
        {
            l5->W->data[i][j] = ((float64_t)rand() / RAND_MAX * 2.0 - 1.0) * xav5;
        }
    }

    struct dropout_layer *drop = dropout_create(0.2);

    struct float_array *x = create_float_array(in_dim);
    struct float_array *a1 = create_float_array(h1);
    struct float_array *a1_bn = create_float_array(h1);
    struct float_array *a1_drop = create_float_array(h1);

    struct float_array *a2 = create_float_array(h2);
    struct float_array *a2_bn = create_float_array(h2);
    struct float_array *a2_drop = create_float_array(h2);

    struct float_array *a3 = create_float_array(h3);
    struct float_array *a3_bn = create_float_array(h3);
    struct float_array *a3_drop = create_float_array(h3);

    struct float_array *a4 = create_float_array(h4);
    struct float_array *a4_bn = create_float_array(h4);
    struct float_array *a4_drop = create_float_array(h4);

    struct float_array *logits = create_float_array(out_dim);
    struct float_array *probs = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    if (!x || !a1 || !a1_bn || !a1_drop || !a2 || !a2_bn || !a2_drop || !a3 || !a3_bn || !a3_drop ||
        !a4 || !a4_bn || !a4_drop || !logits || !probs || !grad_out)
    {
        printf("alloc fail\n");
        return 1;
    }

    const size_t N = 1200;
    float64_t data[N][in_dim];
    size_t labels[N];

    float64_t centers[out_dim][in_dim];
    for (size_t k = 0; k < out_dim; k++)
    {
        for (size_t j = 0; j < in_dim; j++)
        {
            centers[k][j] = 0.2 + 0.6 * ((float64_t)k / (float64_t)(out_dim - 1));
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        const size_t y = rand() % out_dim;
        labels[i] = y;

        for (size_t j = 0; j < in_dim; j++)
        {
            data[i][j] = centers[y][j] + ((float64_t)rand() / RAND_MAX - 0.5) * 0.3;
        }
    }

    for (int epoch = 0; epoch < 600; epoch++)
    {
        const size_t batch_size = 64;
        float64_t epoch_loss = 0.0;

        size_t indices[N];
        for (size_t i = 0; i < N; i++)
        {
            indices[i] = i;
        }

        for (size_t i = 0; i < N; i++)
        {
            size_t j = rand() % N;

            size_t tmp = indices[i];
            indices[i] = indices[j];
            indices[j] = tmp;
        }

        for (size_t bstart = 0; bstart < N; bstart += batch_size)
        {
            const float64_t eps = 1e-8;
            const float64_t beta2 = 0.999;
            const float64_t beta1 = 0.9;
            const float64_t lr = 0.005;

            const size_t bend = bstart + batch_size <= N ? bstart + batch_size : N;
            const size_t cur_batch = bend - bstart;

            struct float_matrix *acc_dW5 = create_float_matrix(l5->out_dim, l5->in_dim);
            struct float_array *acc_db5 = create_float_array(l5->out_dim);

            struct float_matrix *acc_dW4 = create_float_matrix(l4->out_dim, l4->in_dim);
            struct float_array *acc_db4 = create_float_array(l4->out_dim);

            struct float_matrix *acc_dW3 = create_float_matrix(l3->out_dim, l3->in_dim);
            struct float_array *acc_db3 = create_float_array(l3->out_dim);

            struct float_matrix *acc_dW2 = create_float_matrix(l2->out_dim, l2->in_dim);
            struct float_array *acc_db2 = create_float_array(l2->out_dim);

            struct float_matrix *acc_dW1 = create_float_matrix(l1->out_dim, l1->in_dim);
            struct float_array *acc_db1 = create_float_array(l1->out_dim);

            struct float_array *acc_dg1 = create_float_array(bn1->dim);
            struct float_array *acc_dbeta1 = create_float_array(bn1->dim);
            struct float_array *acc_dg2 = create_float_array(bn2->dim);
            struct float_array *acc_dbeta2 = create_float_array(bn2->dim);
            struct float_array *acc_dg3 = create_float_array(bn3->dim);
            struct float_array *acc_dbeta3 = create_float_array(bn3->dim);
            struct float_array *acc_dg4 = create_float_array(bn4->dim);
            struct float_array *acc_dbeta4 = create_float_array(bn4->dim);

            for (size_t si = bstart; si < bend; si++)
            {
                const size_t s = indices[si];

                for (size_t j = 0; j < in_dim; j++)
                {
                    x->data[j] = data[s][j];
                }

                dense_forward(l1, x, a1);
                batchnorm_forward(bn1, a1, a1_bn);
                relu_inplace(a1_bn);
                dropout_forward(drop, a1_bn, a1_drop, 1);

                dense_forward(l2, a1_drop, a2);
                batchnorm_forward(bn2, a2, a2_bn);
                relu_inplace(a2_bn);
                dropout_forward(drop, a2_bn, a2_drop, 1);

                dense_forward(l3, a2_drop, a3);
                batchnorm_forward(bn3, a3, a3_bn);
                relu_inplace(a3_bn);
                dropout_forward(drop, a3_bn, a3_drop, 1);

                dense_forward(l4, a3_drop, a4);
                batchnorm_forward(bn4, a4, a4_bn);
                relu_inplace(a4_bn);
                dropout_forward(drop, a4_bn, a4_drop, 1);

                dense_forward(l5, a4_drop, logits);

                for (size_t i = 0; i < out_dim; i++)
                {
                    probs->data[i] = logits->data[i];
                }

                softmax_inplace(probs);

                const float64_t loss = cross_entropy_loss_from_probs(probs, labels[s]);
                epoch_loss += loss;

                cross_entropy_grad_from_probs(probs, labels[s], grad_out);

                struct float_matrix *dW5 = NULL;
                struct float_array *db5 = NULL;
                struct float_array *d_a4 = create_float_array(h4);

                dense_backward(l5, a4_drop, grad_out, &dW5, &db5, d_a4);

                for (size_t i = 0; i < dW5->rows; i++)
                {
                    for (size_t j = 0; j < dW5->cols; j++)
                    {
                        acc_dW5->data[i][j] += dW5->data[i][j];
                    }
                }

                for (size_t i = 0; i < db5->size; i++)
                {
                    acc_db5->data[i] += db5->data[i];
                }

                free_float_matrix(&dW5);
                free_float_array(&db5);

                struct float_array *d_a4_pre = create_float_array(h4);
                dropout_backward(drop, d_a4, d_a4_pre);

                struct float_array *d_bn4_in = create_float_array(h4);
                struct float_array *dg4 = NULL;
                struct float_array *dbt4 = NULL;

                dense_backward(l4, a3_drop, d_a4_pre, NULL, NULL, d_bn4_in);
                batchnorm_backward(bn4, d_bn4_in, d_a4_pre, &dg4, &dbt4);

                struct float_matrix *dW4 = NULL;
                struct float_array *db4 = NULL;
                struct float_array *d_a3 = create_float_array(h3);

                dense_backward(l4, a3_drop, d_a4_pre, &dW4, &db4, d_a3);

                for (size_t i = 0; i < dW4->rows; i++)
                {
                    for (size_t j = 0; j < dW4->cols; j++)
                    {
                        acc_dW4->data[i][j] += dW4->data[i][j];
                    }
                }

                for (size_t i = 0; i < db4->size; i++)
                {
                    acc_db4->data[i] += db4->data[i];
                }

                for (size_t i = 0; i < dg4->size; i++)
                {
                    acc_dg4->data[i] += dg4->data[i];
                    acc_dbeta4->data[i] += dbt4->data[i];
                }

                free_float_matrix(&dW4);
                free_float_array(&db4);
                free_float_array(&dg4);
                free_float_array(&dbt4);

                free_float_array(&d_bn4_in);

                struct float_array *d_a3_pre = create_float_array(h3);
                dropout_backward(drop, d_a3, d_a3_pre);

                struct float_array *dg3 = NULL;
                struct float_array *dbt3 = NULL;
                struct float_matrix *dW3 = NULL;
                struct float_array *db3 = NULL;
                struct float_array *d_a2 = create_float_array(h2);

                dense_backward(l3, a2_drop, d_a3_pre, &dW3, &db3, d_a2);

                for (size_t i = 0; i < dW3->rows; i++)
                {
                    for (size_t j = 0; j < dW3->cols; j++)
                    {
                        acc_dW3->data[i][j] += dW3->data[i][j];
                    }
                }

                for (size_t i = 0; i < db3->size; i++)
                {
                    acc_db3->data[i] += db3->data[i];
                }

                batchnorm_backward(bn3, d_a2, d_a3_pre, &dg3, &dbt3);

                for (size_t i = 0; i < dg3->size; i++)
                {
                    acc_dg3->data[i] += dg3->data[i];
                    acc_dbeta3->data[i] += dbt3->data[i];
                }

                free_float_matrix(&dW3); free_float_array(&db3); free_float_array(&dg3); free_float_array(&dbt3);

                struct float_array *d_a2_pre = create_float_array(h2);
                dropout_backward(drop, d_a2, d_a2_pre);

                struct float_array *dg2 = NULL; struct float_array *dbt2 = NULL;
                struct float_matrix *dW2 = NULL; struct float_array *db2 = NULL; struct float_array *d_a1 = create_float_array(h1);
                dense_backward(l2, a1_drop, d_a2_pre, &dW2, &db2, d_a1);

                for (size_t i = 0; i < dW2->rows; i++) for (size_t j = 0; j < dW2->cols; j++) acc_dW2->data[i][j] += dW2->data[i][j];
                for (size_t i = 0; i < db2->size; i++) acc_db2->data[i] += db2->data[i];

                batchnorm_backward(bn2, d_a1, d_a2_pre, &dg2, &dbt2);
                for (size_t i = 0; i < dg2->size; i++) { acc_dg2->data[i] += dg2->data[i]; acc_dbeta2->data[i] += dbt2->data[i]; }

                free_float_matrix(&dW2); free_float_array(&db2); free_float_array(&dg2); free_float_array(&dbt2);

                struct float_array *d_a1_pre = create_float_array(h1);
                dropout_backward(drop, d_a1, d_a1_pre);

                struct float_array *dg1 = NULL; struct float_array *dbt1 = NULL;
                struct float_matrix *dW1 = NULL; struct float_array *db1 = NULL; struct float_array *d_x = create_float_array(in_dim);
                dense_backward(l1, x, d_a1_pre, &dW1, &db1, d_x);

                for (size_t i = 0; i < dW1->rows; i++) for (size_t j = 0; j < dW1->cols; j++) acc_dW1->data[i][j] += dW1->data[i][j];
                for (size_t i = 0; i < db1->size; i++) acc_db1->data[i] += db1->data[i];

                batchnorm_backward(bn1, d_x, d_a1_pre, &dg1, &dbt1);
                for (size_t i = 0; i < dg1->size; i++) { acc_dg1->data[i] += dg1->data[i]; acc_dbeta1->data[i] += dbt1->data[i]; }

                free_float_matrix(&dW1); free_float_array(&db1); free_float_array(&dg1); free_float_array(&dbt1);
                free_float_array(&d_x);
                free_float_array(&d_a1);
                free_float_array(&d_a1_pre);
                free_float_array(&d_a2_pre);
                free_float_array(&d_a3_pre);
                free_float_array(&d_a4_pre);
                free_float_array(&d_a2);
                free_float_array(&d_a3);
                free_float_array(&d_a4);
            }

            const double inv_bs = 1.0 / (double)cur_batch;
            // average accumulated gradients
            for (size_t i = 0; i < acc_dW5->rows; i++) for (size_t j = 0; j < acc_dW5->cols; j++) acc_dW5->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db5->size; i++) acc_db5->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW4->rows; i++) for (size_t j = 0; j < acc_dW4->cols; j++) acc_dW4->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db4->size; i++) acc_db4->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW3->rows; i++) for (size_t j = 0; j < acc_dW3->cols; j++) acc_dW3->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db3->size; i++) acc_db3->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW2->rows; i++) for (size_t j = 0; j < acc_dW2->cols; j++) acc_dW2->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db2->size; i++) acc_db2->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW1->rows; i++) for (size_t j = 0; j < acc_dW1->cols; j++) acc_dW1->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db1->size; i++) acc_db1->data[i] *= inv_bs;

            for (size_t i = 0; i < acc_dg1->size; i++) { acc_dg1->data[i] *= inv_bs; acc_dbeta1->data[i] *= inv_bs; }
            for (size_t i = 0; i < acc_dg2->size; i++) { acc_dg2->data[i] *= inv_bs; acc_dbeta2->data[i] *= inv_bs; }
            for (size_t i = 0; i < acc_dg3->size; i++) { acc_dg3->data[i] *= inv_bs; acc_dbeta3->data[i] *= inv_bs; }
            for (size_t i = 0; i < acc_dg4->size; i++) { acc_dg4->data[i] *= inv_bs; acc_dbeta4->data[i] *= inv_bs; }

            // apply updates
            adam_update_dense(l5, acc_dW5, acc_db5, lr, beta1, beta2, eps);
            adam_update_dense(l4, acc_dW4, acc_db4, lr, beta1, beta2, eps);
            adam_update_dense(l3, acc_dW3, acc_db3, lr, beta1, beta2, eps);
            adam_update_dense(l2, acc_dW2, acc_db2, lr, beta1, beta2, eps);
            adam_update_dense(l1, acc_dW1, acc_db1, lr, beta1, beta2, eps);

            batchnorm_apply_adam_update(bn4, acc_dg4, acc_dbeta4, lr, beta1, beta2, eps);
            batchnorm_apply_adam_update(bn3, acc_dg3, acc_dbeta3, lr, beta1, beta2, eps);
            batchnorm_apply_adam_update(bn2, acc_dg2, acc_dbeta2, lr, beta1, beta2, eps);
            batchnorm_apply_adam_update(bn1, acc_dg1, acc_dbeta1, lr, beta1, beta2, eps);

            free_float_matrix(&acc_dW5); free_float_array(&acc_db5);
            free_float_matrix(&acc_dW4); free_float_array(&acc_db4);
            free_float_matrix(&acc_dW3); free_float_array(&acc_db3);
            free_float_matrix(&acc_dW2); free_float_array(&acc_db2);
            free_float_matrix(&acc_dW1); free_float_array(&acc_db1);

            free_float_array(&acc_dg1); free_float_array(&acc_dbeta1);
            free_float_array(&acc_dg2); free_float_array(&acc_dbeta2);
            free_float_array(&acc_dg3); free_float_array(&acc_dbeta3);
            free_float_array(&acc_dg4); free_float_array(&acc_dbeta4);
        }

        if (epoch % 20 == 0)
        {
            // evaluation
            double eval_loss = 0.0; size_t correct = 0;
            for (size_t s = 0; s < N; s++)
            {
                for (size_t j = 0; j < in_dim; j++) x->data[j] = data[s][j];

                dense_forward(l1, x, a1); batchnorm_forward(bn1, a1, a1_bn); relu_inplace(a1_bn); dropout_forward(drop, a1_bn, a1_drop, 0);
                dense_forward(l2, a1_drop, a2); batchnorm_forward(bn2, a2, a2_bn); relu_inplace(a2_bn); dropout_forward(drop, a2_bn, a2_drop, 0);
                dense_forward(l3, a2_drop, a3); batchnorm_forward(bn3, a3, a3_bn); relu_inplace(a3_bn); dropout_forward(drop, a3_bn, a3_drop, 0);
                dense_forward(l4, a3_drop, a4); batchnorm_forward(bn4, a4, a4_bn); relu_inplace(a4_bn); dropout_forward(drop, a4_bn, a4_drop, 0);
                dense_forward(l5, a4_drop, logits);
                for (size_t i = 0; i < out_dim; i++) probs->data[i] = logits->data[i];
                softmax_inplace(probs);
                eval_loss += cross_entropy_loss_from_probs(probs, labels[s]);

                size_t pred = 0; double best = probs->data[0];
                for (size_t i = 1; i < out_dim; i++) if (probs->data[i] > best) { best = probs->data[i]; pred = i; }
                if (pred == labels[s]) correct++;
            }

            printf("epoch %d eval_loss=%.6f accuracy=%.2f%%\n", epoch, eval_loss / (double)N, (double)correct * 100.0 / (double)N);
        }
    }

    dense_free(&l1); dense_free(&l2); dense_free(&l3); dense_free(&l4); dense_free(&l5);
    batchnorm_free(&bn1); batchnorm_free(&bn2); batchnorm_free(&bn3); batchnorm_free(&bn4);
    dropout_free(&drop);

    free_float_array(&x);
    free_float_array(&a1); free_float_array(&a1_bn); free_float_array(&a1_drop);
    free_float_array(&a2); free_float_array(&a2_bn); free_float_array(&a2_drop);
    free_float_array(&a3); free_float_array(&a3_bn); free_float_array(&a3_drop);
    free_float_array(&a4); free_float_array(&a4_bn); free_float_array(&a4_drop);
    free_float_array(&logits); free_float_array(&probs); free_float_array(&grad_out);

    return 0;
}
