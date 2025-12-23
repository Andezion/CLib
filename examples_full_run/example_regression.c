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
    srand(2);
    const size_t in_dim = 1;
    const size_t out_dim = 1;

    struct dense_layer *lin = dense_create(in_dim, out_dim);
    if (!lin) { printf("alloc fail\n"); return 1; }

    struct float_array *x = create_float_array(in_dim);
    struct float_array *y = create_float_array(out_dim);
    struct float_array *t = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    const int N = 100;
    double xs[N], ys[N];
    for (int i = 0; i < N; i++) { xs[i] = -1.0 + 2.0 * i / (N - 1); ys[i] = 2.0 * xs[i] + 1.0 + ((rand()%100)/1000.0 - 0.05); }

    const double lr = 0.1;
    for (int epoch = 0; epoch < 300; epoch++)
    {
        double loss = 0.0;
        for (int i = 0; i < N; i++)
        {
            x->data[0] = xs[i];
            dense_forward(lin, x, y);
            /* linear output */
            t->data[0] = ys[i];
            loss += mse_loss(y, t);
            mse_grad(y, t, grad_out);

            struct float_matrix *dW = NULL; struct float_array *db = NULL;
            struct float_array *d_x = create_float_array(in_dim);
            dense_backward(lin, x, grad_out, &dW, &db, d_x);

            sgd_update_dense(lin, dW, db, lr);

            free_float_matrix(&dW); free_float_array(&db); free_float_array(&d_x);
        }
        if (epoch % 50 == 0) printf("epoch %d loss=%.6f\n", epoch, loss / N);
    }

    printf("Learned mapping samples:\n");
    for (int i = 0; i < 10; i++)
    {
        double vx = -1.0 + 2.0 * i / 9.0;
        x->data[0] = vx;
        dense_forward(lin, x, y);
        printf("x=%.3f -> y=%.3f (true=%.3f)\n", vx, y->data[0], 2.0*vx + 1.0);
    }

    dense_free(&lin);
    free_float_array(&x); free_float_array(&y); free_float_array(&t); free_float_array(&grad_out);
    return 0;
}
