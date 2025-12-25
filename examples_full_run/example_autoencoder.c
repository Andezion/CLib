#include <stdio.h>
#include <stdlib.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "array/array.h"

int main(void)
{
    srand(3);

    const size_t in_dim = 8;
    const size_t bottleneck = 3;

    struct float_array *x = create_float_array(in_dim);
    struct float_array *h1 = create_float_array(6);
    struct float_array *code = create_float_array(bottleneck);
    struct float_array *h2 = create_float_array(6);
    struct float_array *y = create_float_array(in_dim);
    struct float_array *grad_out = create_float_array(in_dim);

    struct dense_layer *e1 = dense_create(in_dim, 6);
    struct dense_layer *e2 = dense_create(6, bottleneck);
    struct dense_layer *d1 = dense_create(bottleneck, 6);
    struct dense_layer *d2 = dense_create(6, in_dim);

    if (!x || !h1 || !code || !h2 || !y || !grad_out || !e1 || !e2 || !d1 || !d2)
    {
        printf("alloc fail\n");
        return 1;
    }

    for (int epoch = 0; epoch < 800; epoch++)
    {
        float64_t loss_sum = 0.0;
        for (int it = 0; it < 200; it++)
        {
            for (size_t d = 0; d < in_dim; d++)
            {
                x->data[d] = ((float64_t) rand() / RAND_MAX - 0.5) * 2.0;
            }

            dense_forward(e1, x, h1);
            tanh_inplace(h1);

            dense_forward(e2, h1, code);
            tanh_inplace(code);

            dense_forward(d1, code, h2);
            tanh_inplace(h2);

            dense_forward(d2, h2, y);

            loss_sum += mse_loss(y, x);

            mse_grad(y, x, grad_out);

            struct float_matrix *dW4 = NULL; struct float_array *db4 = NULL;
            struct float_array *d_h2 = create_float_array(6);

            dense_backward(d2, h2, grad_out, &dW4, &db4, d_h2);
            sgd_update_dense(d2, dW4, db4, 0.02);
            free_float_matrix(&dW4); free_float_array(&db4);

            struct float_matrix *dW3 = NULL; struct float_array *db3 = NULL;
            struct float_array *d_code = create_float_array(bottleneck);

            dense_backward(d1, code, d_h2, &dW3, &db3, d_code);
            sgd_update_dense(d1, dW3, db3, 0.02);
            free_float_matrix(&dW3); free_float_array(&db3);

            struct float_matrix *dW2 = NULL; struct float_array *db2 = NULL;
            struct float_array *d_h1 = create_float_array(6);

            dense_backward(e2, h1, d_code, &dW2, &db2, d_h1);
            sgd_update_dense(e2, dW2, db2, 0.02);
            free_float_matrix(&dW2); free_float_array(&db2);

            struct float_matrix *dW1 = NULL; struct float_array *db1 = NULL;
            struct float_array *d_x = create_float_array(in_dim);

            dense_backward(e1, x, d_h1, &dW1, &db1, d_x);
            sgd_update_dense(e1, dW1, db1, 0.02);
            free_float_matrix(&dW1); free_float_array(&db1);

            free_float_array(&d_h2);
            free_float_array(&d_code);
            free_float_array(&d_h1);
            free_float_array(&d_x);
        }

        if (epoch % 200 == 0)
        {
            printf("epoch %d loss=%.6f\n", epoch, loss_sum / 200.0);
        }
    }

    for (int t = 0; t < 5; t++)
    {
        for (size_t d = 0; d < in_dim; d++)
        {
            x->data[d] = ((double)rand() / RAND_MAX - 0.5) * 2.0;
        }

        dense_forward(e1, x, h1);
        tanh_inplace(h1);

        dense_forward(e2, h1, code);
        tanh_inplace(code);

        dense_forward(d1, code, h2);
        tanh_inplace(h2);

        dense_forward(d2, h2, y);

        printf("orig:");
        for (size_t d = 0; d < in_dim; d++)
        {
            printf(" %.3f", x->data[d]);
        }

        printf("\nrecon:");
        for (size_t d = 0; d < in_dim; d++)
        {
            printf(" %.3f", y->data[d]);
        }
        printf("\n");
    }

    dense_free(&e1);
    dense_free(&e2);
    dense_free(&d1);
    dense_free(&d2);

    free_float_array(&x);
    free_float_array(&h1);
    free_float_array(&code);
    free_float_array(&h2);
    free_float_array(&y);
    free_float_array(&grad_out);

    return 0;
}
