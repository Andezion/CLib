#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "../nn/dropout.h"
#include "array/array.h"

int main(void)
{
    srand((unsigned)time(NULL));

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

    for (size_t i = 0; i < l1->W->rows; i++) 
    {
        for (size_t j = 0; j < l1->W->cols; j++) 
        {
            l1->W->data[i][j] = ((double)rand()/RAND_MAX - 0.5) * 0.2;
        }
    }

    for (size_t i = 0; i < l2->W->rows; i++) 
    {
        for (size_t j = 0; j < l2->W->cols; j++) 
        {
            l2->W->data[i][j] = ((double)rand()/RAND_MAX - 0.5) * 0.2;
        }
    }
    
    for (size_t i = 0; i < l3->W->rows; i++) 
    {
        for (size_t j = 0; j < l3->W->cols; j++) 
        {
            l3->W->data[i][j] = ((double)rand()/RAND_MAX - 0.5) * 0.2;
        }
    }

    struct dropout_layer *drop = dropout_create(0.3);

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

    const size_t N = 6;
    double data[N][in_dim];
    size_t labels[N];
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < in_dim; j++)
        {
            data[i][j] = (double)rand() / RAND_MAX;
        }
        labels[i] = i % out_dim;
    }

    const double lr = 0.5;
    for (int epoch = 0; epoch < 200; epoch++)
    {
        double epoch_loss = 0.0;
        for (size_t s = 0; s < N; s++)
        {
            for (size_t j = 0; j < in_dim; j++) 
            {
                x->data[j] = data[s][j];
            }

            dense_forward(l1, x, a1);
            relu_inplace(a1);
            dropout_forward(drop, a1, a1_drop, 1);

            dense_forward(l2, a1_drop, a2);
            relu_inplace(a2);
            dropout_forward(drop, a2, a2_drop, 1);

            dense_forward(l3, a2_drop, logits);

            for (size_t i = 0; i < out_dim; i++) 
            {
                probs->data[i] = logits->data[i];
            }

            softmax_inplace(probs);

            const double loss = cross_entropy_loss_from_probs(probs, labels[s]);
            epoch_loss += loss;

            cross_entropy_grad_from_probs(probs, labels[s], grad_out);

            struct float_matrix *dW3 = NULL; 
            struct float_array *db3 = NULL; 

            struct float_array *d_a2 = create_float_array(h2);
            
            dense_backward(l3, a2_drop, grad_out, &dW3, &db3, d_a2);
            sgd_update_dense(l3, dW3, db3, lr);
            free_float_matrix(&dW3); free_float_array(&db3);

            struct float_array *d_a2_pre = create_float_array(h2);
            dropout_backward(drop, d_a2, d_a2_pre);

            struct float_matrix *dW2 = NULL; struct float_array *db2 = NULL; struct float_array *d_a1 = create_float_array(h1);
            dense_backward(l2, a1_drop, d_a2_pre, &dW2, &db2, d_a1);
            sgd_update_dense(l2, dW2, db2, lr);
            free_float_matrix(&dW2); free_float_array(&db2);

            free_float_array(&d_a2); free_float_array(&d_a2_pre);

            struct float_array *d_a1_pre = create_float_array(h1);
            dropout_backward(drop, d_a1, d_a1_pre);

            struct float_matrix *dW1 = NULL; struct float_array *db1 = NULL; struct float_array *d_x = create_float_array(in_dim);
            dense_backward(l1, x, d_a1_pre, &dW1, &db1, d_x);
            sgd_update_dense(l1, dW1, db1, lr);
            free_float_matrix(&dW1); free_float_array(&db1);

            free_float_array(&d_a1); free_float_array(&d_a1_pre); free_float_array(&d_x);
        }

        if (epoch % 20 == 0)
        {
            printf("epoch %d avg_loss=%.6f\n", epoch, epoch_loss / N);
        }
    }

    dense_free(&l1); dense_free(&l2); dense_free(&l3);
    dropout_free(&drop);
    free_float_array(&x); free_float_array(&a1); free_float_array(&a1_drop); free_float_array(&a2); free_float_array(&a2_drop);
    free_float_array(&logits); free_float_array(&probs); free_float_array(&grad_out);

    return 0;
}
