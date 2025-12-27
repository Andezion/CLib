#include <stdio.h>
#include <stdlib.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "../nn/dropout.h"
#include "../nn/batchnorm.h"
#include "array/array.h"

int main(void)
{
    srand(2);

    const size_t in_dim = 4;
    const size_t h1 = 32;
    const size_t h2 = 24;
    const size_t out_dim = 3;

    struct dense_layer *l1 = dense_create(in_dim, h1);
    struct batchnorm_layer *bn1 = batchnorm_create(h1);

    struct dense_layer *l2 = dense_create(h1, h2);
    struct batchnorm_layer *bn2 = batchnorm_create(h2);

    struct dense_layer *l3 = dense_create(h2, out_dim);

    if (!l1 || !bn1 || !l2 || !bn2 || !l3)
    {
        printf("failed to create layers\n");
        return 1;
    }

    struct dropout_layer *drop = dropout_create(0.0);

    struct float_array *x = create_float_array(in_dim);
    struct float_array *a1 = create_float_array(h1);
    struct float_array *a1_bn = create_float_array(h1);
    struct float_array *a2 = create_float_array(h2);
    struct float_array *a2_bn = create_float_array(h2);
    struct float_array *logits = create_float_array(out_dim);
    struct float_array *probs = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    if (!x || !a1 || !a1_bn || !a2 || !a2_bn || !logits || !probs || !grad_out)
    {
        printf("alloc fail\n");
        return 1;
    }

    const size_t n_classes = 3;
    const size_t per_class = 50;
    const size_t N = n_classes * per_class;

    float64_t centers[3][4] = {{5.1, 3.5, 1.4, 0.2},
                             {5.9, 3.0, 4.2, 1.5},
                             {6.3, 3.3, 6.0, 2.5}};

    float64_t data[N][in_dim];
    size_t labels[N];

    for (size_t cls = 0; cls < n_classes; cls++)
    {
        for (size_t i = 0; i < per_class; i++)
        {
            size_t idx = cls * per_class + i;
            labels[idx] = cls;

            for (size_t d = 0; d < in_dim; d++)
            {
                float64_t noise = ((float64_t) rand() / RAND_MAX - 0.5) * 0.6;
                data[idx][d] = centers[cls][d] + noise;
            }
        }
    }

    size_t indices[N];
    for (size_t i = 0; i < N; i++)
    {
        indices[i] = i;
    }

    for (size_t i = 0; i < N; i++)
    {
        size_t j = rand() % N;
        size_t t = indices[i];

        indices[i] = indices[j];
        indices[j] = t;
    }

    const size_t train_N = (size_t)((float64_t)N * 0.8);
    const size_t val_N = N - train_N;

    size_t train_idx[train_N];
    size_t val_idx[val_N];

    for (size_t i = 0; i < train_N; i++)
    {
        train_idx[i] = indices[i];
    }

    for (size_t i = 0; i < val_N; i++)
    {
        val_idx[i] = indices[train_N + i];
    }

    float64_t lr = 0.01;
    float64_t best_val = 1e308;

    int best_epoch = -1;
    int wait = 0;

    for (int epoch = 0; epoch < 500; epoch++)
    {
        int patience = 20;
        const size_t batch_size = 16;

        for (size_t i = 0; i < train_N; i++)
        {
            size_t j = rand() % train_N;
            size_t t = train_idx[i];

            train_idx[i] = train_idx[j];
            train_idx[j] = t;
        }

        float64_t train_loss = 0.0;

        for (size_t bstart = 0; bstart < train_N; bstart += batch_size)
        {
            const float64_t eps = 1e-8;
            const float64_t beta2 = 0.999;
            const float64_t beta1 = 0.9;

            size_t bend = bstart + batch_size <= train_N ? bstart + batch_size : train_N;
            size_t cur_bs = bend - bstart;

            struct float_matrix *acc_dW3 = create_float_matrix(l3->out_dim, l3->in_dim);
            struct float_array *acc_db3 = create_float_array(l3->out_dim);

            struct float_matrix *acc_dW2 = create_float_matrix(l2->out_dim, l2->in_dim);
            struct float_array *acc_db2 = create_float_array(l2->out_dim);

            struct float_matrix *acc_dW1 = create_float_matrix(l1->out_dim, l1->in_dim);
            struct float_array *acc_db1 = create_float_array(l1->out_dim);

            struct float_array *acc_dgamma2 = create_float_array(bn2->dim);
            struct float_array *acc_dbeta2 = create_float_array(bn2->dim);
            struct float_array *acc_dgamma1 = create_float_array(bn1->dim);
            struct float_array *acc_dbeta1 = create_float_array(bn1->dim);

            for (size_t si = bstart; si < bend; si++)
            {
                size_t s = train_idx[si];
                for (size_t j = 0; j < in_dim; j++)
                {
                    x->data[j] = data[s][j];
                }

                dense_forward(l1, x, a1);
                batchnorm_forward(bn1, a1, a1_bn);
                relu_inplace(a1_bn);

                dense_forward(l2, a1_bn, a2);
                batchnorm_forward(bn2, a2, a2_bn);
                relu_inplace(a2_bn);

                dense_forward(l3, a2_bn, logits);

                for (size_t i = 0; i < out_dim; i++)
                {
                    probs->data[i] = logits->data[i];
                }

                softmax_inplace(probs);

                float64_t loss = cross_entropy_loss_from_probs(probs, labels[s]);
                train_loss += loss;

                cross_entropy_grad_from_probs(probs, labels[s], grad_out);

                struct float_matrix *dW3 = NULL;
                struct float_array *db3 = NULL;
                struct float_array *d_a2 = create_float_array(h2);

                dense_backward(l3, a2_bn, grad_out, &dW3, &db3, d_a2);

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

                free_float_matrix(&dW3);
                free_float_array(&db3);

                struct float_array *d_a2_pre = create_float_array(h2);
                dropout_backward(drop, d_a2, d_a2_pre);

                struct float_matrix *dW2 = NULL;
                struct float_array *db2 = NULL;
                struct float_array *d_a1 = create_float_array(h1);

                dense_backward(l2, a1_bn, d_a2_pre, &dW2, &db2, d_a1);

                for (size_t i = 0; i < dW2->rows; i++)
                {
                    for (size_t j = 0; j < dW2->cols; j++)
                    {
                        acc_dW2->data[i][j] += dW2->data[i][j];
                    }
                }

                for (size_t i = 0; i < db2->size; i++)
                {
                    acc_db2->data[i] += db2->data[i];
                }

                free_float_matrix(&dW2);
                free_float_array(&db2);

                struct float_array *d_a2_bn_pre = create_float_array(h2);
                struct float_array *d_gamma2 = NULL;
                struct float_array *d_beta2 = NULL;

                batchnorm_backward(bn2, d_a2_pre, d_a2_bn_pre, &d_gamma2, &d_beta2);

                for (size_t i = 0; i < d_gamma2->size; i++)
                {
                    acc_dgamma2->data[i] += d_gamma2->data[i];
                }

                for (size_t i = 0; i < d_beta2->size; i++)
                {
                    acc_dbeta2->data[i] += d_beta2->data[i];
                }

                free_float_array(&d_gamma2);
                free_float_array(&d_beta2);

                struct float_array *d_a1_pre = create_float_array(h1);
                dropout_backward(drop, d_a1, d_a1_pre);

                struct float_matrix *dW1 = NULL;
                struct float_array *db1 = NULL;
                struct float_array *d_x = create_float_array(in_dim);

                dense_backward(l1, x, d_a1_pre, &dW1, &db1, d_x);

                for (size_t i = 0; i < dW1->rows; i++)
                {
                    for (size_t j = 0; j < dW1->cols; j++)
                    {
                        acc_dW1->data[i][j] += dW1->data[i][j];
                    }
                }

                for (size_t i = 0; i < db1->size; i++)
                {
                    acc_db1->data[i] += db1->data[i];
                }

                free_float_matrix(&dW1);
                free_float_array(&db1);

                struct float_array *d_gamma1 = NULL;
                struct float_array *d_beta1 = NULL;

                batchnorm_backward(bn1, d_a1_pre, NULL, &d_gamma1, &d_beta1);

                for (size_t i = 0; i < d_gamma1->size; i++)
                {
                    acc_dgamma1->data[i] += d_gamma1->data[i];
                }
                for (size_t i = 0; i < d_beta1->size; i++)
                {
                    acc_dbeta1->data[i] += d_beta1->data[i];
                }

                free_float_array(&d_gamma1);
                free_float_array(&d_beta1);

                free_float_array(&d_a2);
                free_float_array(&d_a2_pre);
                free_float_array(&d_a2_bn_pre);
                free_float_array(&d_a1);
                free_float_array(&d_a1_pre);
                free_float_array(&d_x);
            }

            double inv_bs = 1.0 / (double)cur_bs;
            for (size_t i = 0; i < acc_dW3->rows; i++) for (size_t j = 0; j < acc_dW3->cols; j++) acc_dW3->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db3->size; i++) acc_db3->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW2->rows; i++) for (size_t j = 0; j < acc_dW2->cols; j++) acc_dW2->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db2->size; i++) acc_db2->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW1->rows; i++) for (size_t j = 0; j < acc_dW1->cols; j++) acc_dW1->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db1->size; i++) acc_db1->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dgamma2->size; i++) acc_dgamma2->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dbeta2->size; i++) acc_dbeta2->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dgamma1->size; i++) acc_dgamma1->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dbeta1->size; i++) acc_dbeta1->data[i] *= inv_bs;

            adam_update_dense(l3, acc_dW3, acc_db3, lr, beta1, beta2, eps);
            adam_update_dense(l2, acc_dW2, acc_db2, lr, beta1, beta2, eps);
            adam_update_dense(l1, acc_dW1, acc_db1, lr, beta1, beta2, eps);

            batchnorm_apply_adam_update(bn2, acc_dgamma2, acc_dbeta2, lr, beta1, beta2, eps);
            batchnorm_apply_adam_update(bn1, acc_dgamma1, acc_dbeta1, lr, beta1, beta2, eps);

            free_float_matrix(&acc_dW3); free_float_array(&acc_db3);
            free_float_matrix(&acc_dW2); free_float_array(&acc_db2);
            free_float_matrix(&acc_dW1); free_float_array(&acc_db1);

            free_float_array(&acc_dgamma2); free_float_array(&acc_dbeta2);
            free_float_array(&acc_dgamma1); free_float_array(&acc_dbeta1);
        }

        double val_loss = 0.0; size_t val_correct = 0;
        for (size_t i = 0; i < val_N; i++)
        {
            size_t s = val_idx[i];
            for (size_t d = 0; d < in_dim; d++) x->data[d] = data[s][d];

            dense_forward(l1, x, a1);
            batchnorm_forward(bn1, a1, a1_bn);
            relu_inplace(a1_bn);

            dense_forward(l2, a1_bn, a2);
            batchnorm_forward(bn2, a2, a2_bn);
            relu_inplace(a2_bn);

            dense_forward(l3, a2_bn, logits);
            for (size_t k = 0; k < out_dim; k++) probs->data[k] = logits->data[k];
            softmax_inplace(probs);

            val_loss += cross_entropy_loss_from_probs(probs, labels[s]);
            size_t pred = 0; double best = probs->data[0];
            for (size_t k = 1; k < out_dim; k++) if (probs->data[k] > best) { best = probs->data[k]; pred = k; }
            if (pred == labels[s]) val_correct++;
        }

        double avg_val = val_loss / (double)val_N;
        if (avg_val < best_val)
        {
            best_val = avg_val; best_epoch = epoch; wait = 0;
        }
        else
        {
            wait++;
        }

        if (epoch > 0 && epoch % 50 == 0) lr *= 0.5;

        if (epoch % 10 == 0)
        {
            printf("epoch %d val_loss=%.6f val_acc=%.2f%% lr=%.5f\n", epoch, avg_val, (double)val_correct*100.0/(double)val_N, lr);
        }

        if (wait >= patience) { printf("early stopping at epoch %d (best epoch %d val_loss=%.6f)\n", epoch, best_epoch, best_val); break; }
    }

    dense_free(&l1); dense_free(&l2); dense_free(&l3);
    batchnorm_free(&bn1); batchnorm_free(&bn2);
    dropout_free(&drop);

    free_float_array(&x); free_float_array(&a1); free_float_array(&a1_bn);
    free_float_array(&a2); free_float_array(&a2_bn); free_float_array(&logits);
    free_float_array(&probs); free_float_array(&grad_out);

    return 0;
}
