#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "../nn/dropout.h"
#include "array/array.h"

int main(void)
{
    srand(0);

    const size_t in_dim = 4;
    const size_t h1 = 16;
    const size_t h2 = 12;
    const size_t out_dim = 3;

    struct dense_layer *l1 = dense_create(in_dim, h1);
    struct dense_layer *l2 = dense_create(h1, h2);
    struct dense_layer *l3 = dense_create(h2, out_dim);

    if (!l1 || !l2 || !l3)
    {
        printf("failed to create layers\n");
        return 1;
    }

    const double xav_l1 = sqrt(6.0 / (l1->in_dim + l1->out_dim));
    const double xav_l2 = sqrt(6.0 / (l2->in_dim + l2->out_dim));
    const double xav_l3 = sqrt(6.0 / (l3->in_dim + l3->out_dim));

    for (size_t i = 0; i < l1->W->rows; i++) 
    {
        for (size_t j = 0; j < l1->W->cols; j++) 
        {
            l1->W->data[i][j] = (((double) rand() / RAND_MAX) * 2.0 - 1.0) * xav_l1;
        }
    }

    for (size_t i = 0; i < l2->W->rows; i++) 
    {
        for (size_t j = 0; j < l2->W->cols; j++) 
        {
            l2->W->data[i][j] = ((double) rand() / RAND_MAX * 2.0 - 1.0) * xav_l2;
        }
    }
    
    for (size_t i = 0; i < l3->W->rows; i++) 
    {
        for (size_t j = 0; j < l3->W->cols; j++) 
        {
            l3->W->data[i][j] = (((double) rand() / RAND_MAX) * 2.0 - 1.0) * xav_l3;
        }
    }

    struct dropout_layer *drop = dropout_create(0.0);

    struct float_array *x = create_float_array(in_dim);
    struct float_array *a1 = create_float_array(h1);
    struct float_array *a1_drop = create_float_array(h1);
    struct float_array *a2 = create_float_array(h2);
    struct float_array *a2_drop = create_float_array(h2);
    struct float_array *logits = create_float_array(out_dim);
    struct float_array *probs = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    if (!x || !a1 || !a1_drop || !a2 || !a2_drop || !logits || !probs || !grad_out)
    {
        printf("alloc fail\n");
        return 1;
    }

    const size_t N = 600;
    double data[N][in_dim];
    size_t labels[N];

    double centers[out_dim][in_dim];
    for (size_t k = 0; k < out_dim; k++)
    {
        for (size_t j = 0; j < in_dim; j++)
        {
            centers[k][j] = 0.2 + 0.6 * ((double) k / (double) (out_dim - 1));
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        const size_t y = rand() % out_dim;
        labels[i] = y;
        for (size_t j = 0; j < in_dim; j++)
        {
            data[i][j] = centers[y][j] + ((double) rand() / RAND_MAX - 0.5) * 0.2;
        }
    }

    for (int epoch = 0; epoch < 1000; epoch++)
    {
        const size_t batch_size = 32;
        double epoch_loss = 0.0;
        double epoch_grad_norm = 0.0;

        size_t indices[N];
        for (size_t i = 0; i < N; i++) indices[i] = i;
        for (size_t i = 0; i < N; i++)
        {
            size_t j = rand() % N;
            size_t tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
        }

        for (size_t bstart = 0; bstart < N; bstart += batch_size)
        {
            const double eps = 1e-8;
            const double beta2 = 0.999;
            const double beta1 = 0.9;
            const double lr = 0.01;
            const size_t bend = (bstart + batch_size <= N) ? (bstart + batch_size) : N;
            const size_t cur_batch = bend - bstart;

            struct float_matrix *acc_dW3 = create_float_matrix(l3->out_dim, l3->in_dim);
            struct float_array *acc_db3 = create_float_array(l3->out_dim);
            struct float_matrix *acc_dW2 = create_float_matrix(l2->out_dim, l2->in_dim);
            struct float_array *acc_db2 = create_float_array(l2->out_dim);
            struct float_matrix *acc_dW1 = create_float_matrix(l1->out_dim, l1->in_dim);
            struct float_array *acc_db1 = create_float_array(l1->out_dim);

            for (size_t si = bstart; si < bend; si++)
            {
                const size_t s = indices[si];
                for (size_t j = 0; j < in_dim; j++) x->data[j] = data[s][j];

                dense_forward(l1, x, a1);
                relu_inplace(a1);
                dropout_forward(drop, a1, a1_drop, 1);

                dense_forward(l2, a1_drop, a2);
                relu_inplace(a2);
                dropout_forward(drop, a2, a2_drop, 1);

                dense_forward(l3, a2_drop, logits);
                for (size_t i = 0; i < out_dim; i++) probs->data[i] = logits->data[i];
                softmax_inplace(probs);

                const double loss = cross_entropy_loss_from_probs(probs, labels[s]);
                epoch_loss += loss;

                cross_entropy_grad_from_probs(probs, labels[s], grad_out);

                struct float_matrix *dW3 = NULL;
                struct float_array *db3 = NULL;
                struct float_array *d_a2 = create_float_array(h2);
                dense_backward(l3, a2_drop, grad_out, &dW3, &db3, d_a2);

                for (size_t i = 0; i < dW3->rows; i++) for (size_t j = 0; j < dW3->cols; j++) acc_dW3->data[i][j] += dW3->data[i][j];
                for (size_t i = 0; i < db3->size; i++) acc_db3->data[i] += db3->data[i];

                free_float_matrix(&dW3); free_float_array(&db3);

                struct float_array *d_a2_pre = create_float_array(h2);
                dropout_backward(drop, d_a2, d_a2_pre);

                struct float_matrix *dW2 = NULL;
                struct float_array *db2 = NULL;
                struct float_array *d_a1 = create_float_array(h1);
                dense_backward(l2, a1_drop, d_a2_pre, &dW2, &db2, d_a1);

                for (size_t i = 0; i < dW2->rows; i++) for (size_t j = 0; j < dW2->cols; j++) acc_dW2->data[i][j] += dW2->data[i][j];
                for (size_t i = 0; i < db2->size; i++) acc_db2->data[i] += db2->data[i];

                free_float_matrix(&dW2); free_float_array(&db2);
                free_float_array(&d_a2); free_float_array(&d_a2_pre);

                struct float_array *d_a1_pre = create_float_array(h1);
                dropout_backward(drop, d_a1, d_a1_pre);

                struct float_matrix *dW1 = NULL;
                struct float_array *db1 = NULL;
                struct float_array *d_x = create_float_array(in_dim);
                dense_backward(l1, x, d_a1_pre, &dW1, &db1, d_x);

                for (size_t i = 0; i < dW1->rows; i++) for (size_t j = 0; j < dW1->cols; j++) acc_dW1->data[i][j] += dW1->data[i][j];
                for (size_t i = 0; i < db1->size; i++) acc_db1->data[i] += db1->data[i];

                free_float_matrix(&dW1); free_float_array(&db1);
                free_float_array(&d_a1); free_float_array(&d_a1_pre); free_float_array(&d_x);
            }

            const double inv_bs = 1.0 / (double) cur_batch;
            for (size_t i = 0; i < acc_dW3->rows; i++) for (size_t j = 0; j < acc_dW3->cols; j++) acc_dW3->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db3->size; i++) acc_db3->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW2->rows; i++) for (size_t j = 0; j < acc_dW2->cols; j++) acc_dW2->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db2->size; i++) acc_db2->data[i] *= inv_bs;
            for (size_t i = 0; i < acc_dW1->rows; i++) for (size_t j = 0; j < acc_dW1->cols; j++) acc_dW1->data[i][j] *= inv_bs;
            for (size_t i = 0; i < acc_db1->size; i++) acc_db1->data[i] *= inv_bs;

            double gnorm = 0.0;
            for (size_t i = 0; i < acc_dW3->rows; i++) for (size_t j = 0; j < acc_dW3->cols; j++) { double v = acc_dW3->data[i][j]; gnorm += v*v; }
            for (size_t i = 0; i < acc_db3->size; i++) { double v = acc_db3->data[i]; gnorm += v*v; }
            for (size_t i = 0; i < acc_dW2->rows; i++) for (size_t j = 0; j < acc_dW2->cols; j++) { double v = acc_dW2->data[i][j]; gnorm += v*v; }
            for (size_t i = 0; i < acc_db2->size; i++) { double v = acc_db2->data[i]; gnorm += v*v; }
            for (size_t i = 0; i < acc_dW1->rows; i++) for (size_t j = 0; j < acc_dW1->cols; j++) { double v = acc_dW1->data[i][j]; gnorm += v*v; }
            for (size_t i = 0; i < acc_db1->size; i++) { double v = acc_db1->data[i]; gnorm += v*v; }
            gnorm = sqrt(gnorm);
            epoch_grad_norm += gnorm;

            adam_update_dense(l3, acc_dW3, acc_db3, lr, beta1, beta2, eps);
            adam_update_dense(l2, acc_dW2, acc_db2, lr, beta1, beta2, eps);
            adam_update_dense(l1, acc_dW1, acc_db1, lr, beta1, beta2, eps);

            free_float_matrix(&acc_dW3); free_float_array(&acc_db3);
            free_float_matrix(&acc_dW2); free_float_array(&acc_db2);
            free_float_matrix(&acc_dW1); free_float_array(&acc_db1);
        }

        double eval_loss = 0.0;
        size_t correct = 0;
        for (size_t s = 0; s < N; s++)
        {
            for (size_t j = 0; j < in_dim; j++) x->data[j] = data[s][j];

            dense_forward(l1, x, a1);
            relu_inplace(a1);
            dropout_forward(drop, a1, a1_drop, 0);

            dense_forward(l2, a1_drop, a2);
            relu_inplace(a2);
            dropout_forward(drop, a2, a2_drop, 0);

            dense_forward(l3, a2_drop, logits);

            for (size_t i = 0; i < out_dim; i++) probs->data[i] = logits->data[i];
            softmax_inplace(probs);
            eval_loss += cross_entropy_loss_from_probs(probs, labels[s]);

            size_t pred = 0;
            double best = probs->data[0];
            for (size_t i = 1; i < out_dim; i++)
            {
                if (probs->data[i] > best)
                {
                    best = probs->data[i];
                    pred = i;
                }
            }

            if (pred == labels[s])
            {
                correct++;
            }
        }

        if (epoch % 20 == 0)
        {
            printf("epoch %d avg_train_loss=%.6f eval_loss=%.6f accuracy=%.2f%%\n",
                   epoch, epoch_loss / (double) N, eval_loss / (double) N, (double)correct * 100.0 / (double) N);
            for (size_t t = 0; t < 3 && t < N; t++)
            {
                for (size_t j = 0; j < in_dim; j++)
                {
                    x->data[j] = data[t][j];
                }

                dense_forward(l1, x, a1);
                relu_inplace(a1);
                dropout_forward(drop, a1, a1_drop, 0);

                dense_forward(l2, a1_drop, a2);
                relu_inplace(a2);
                dropout_forward(drop, a2, a2_drop, 0);

                dense_forward(l3, a2_drop, logits);

                for (size_t i = 0; i < out_dim; i++)
                {
                    probs->data[i] = logits->data[i];
                }
                softmax_inplace(probs);

                printf(" sample %zu probs:", t);

                for (size_t i = 0; i < out_dim; i++)
                {
                    printf(" %.3f", probs->data[i]);
                }

                printf(" label=%zu\n", labels[t]);
            }
        }
    }

    dense_free(&l1); 
    dense_free(&l2); 
    dense_free(&l3);

    dropout_free(&drop);

    free_float_array(&x); 
    free_float_array(&a1); 
    free_float_array(&a1_drop); 
    free_float_array(&a2); 
    free_float_array(&a2_drop);
    free_float_array(&logits); 
    free_float_array(&probs); 
    free_float_array(&grad_out);

    return 0;
}
