#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "array/array.h"

int main(void)
{
    srand(1);

    const size_t in_dim = 2;
    const size_t hid = 4;
    const size_t out_dim = 1;

    struct dense_layer *l1 = dense_create(in_dim, hid);
    struct dense_layer *l2 = dense_create(hid, out_dim);
    if (!l1 || !l2) { printf("alloc fail\n"); return 1; }

    struct float_array *x = create_float_array(in_dim);
    struct float_array *h = create_float_array(hid);
    struct float_array *y = create_float_array(out_dim);
    struct float_array *target = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);
    if (!x || !h || !y || !target || !grad_out) { printf("alloc fail\n"); return 1; }

    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double targets[4] = {0,1,1,0};

    const double lr = 0.8;
    for (int epoch = 0; epoch < 5000; epoch++)
    {
        double loss = 0.0;
        for (size_t i = 0; i < 4; i++)
        {
            x->data[0] = inputs[i][0]; x->data[1] = inputs[i][1];

            dense_forward(l1, x, h);
            tanh_inplace(h);

            dense_forward(l2, h, y);
            sigmoid_inplace(y);

            target->data[0] = targets[i];
            loss += mse_loss(y, target);

            mse_grad(y, target, grad_out);

            struct float_matrix *dW2 = NULL; struct float_array *db2 = NULL;
            struct float_array *d_h = create_float_array(hid);
            dense_backward(l2, h, grad_out, &dW2, &db2, d_h);

            sgd_update_dense(l2, dW2, db2, lr);

            free_float_matrix(&dW2); free_float_array(&db2);

            struct float_array *d_h_pre = create_float_array(hid);
            sigmoid_grad(h, d_h_pre); /* reuse as placeholder */

            struct float_matrix *dW1 = NULL; struct float_array *db1 = NULL;
            struct float_array *d_x = create_float_array(in_dim);
            dense_backward(l1, x, d_h, &dW1, &db1, d_x);

            sgd_update_dense(l1, dW1, db1, lr);

            free_float_matrix(&dW1); free_float_array(&db1);
            free_float_array(&d_h); free_float_array(&d_h_pre); free_float_array(&d_x);
        }
        if (epoch % 1000 == 0) printf("epoch %d loss=%.6f\n", epoch, loss);
    }

    printf("Trained XOR predictions:\n");
    for (size_t i = 0; i < 4; i++)
    {
        x->data[0] = inputs[i][0]; x->data[1] = inputs[i][1];
        dense_forward(l1, x, h); tanh_inplace(h);
        dense_forward(l2, h, y); sigmoid_inplace(y);
        printf("[%g,%g] -> %.3f (target %.0f)\n", inputs[i][0], inputs[i][1], y->data[0], targets[i]);
    }

    dense_free(&l1); dense_free(&l2);
    free_float_array(&x); free_float_array(&h); free_float_array(&y); free_float_array(&target); free_float_array(&grad_out);
    return 0;
}
