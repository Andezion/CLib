#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "array/array.h"

int main(void)
{
    srand(2);

    const size_t per_class = 200;
    const size_t N = per_class * 2;
    const size_t in_dim = 2;

    struct float_array *x = create_float_array(in_dim);
    struct float_array *h = create_float_array(32);
    struct float_array *y = create_float_array(1);

    struct float_array *target = create_float_array(1);
    struct float_array *grad_out = create_float_array(1);

    struct dense_layer *l1 = dense_create(in_dim, 32);
    struct dense_layer *l2 = dense_create(32, 1);

    if (!x || !h || !y || !target || !grad_out || !l1 || !l2)
    {
        printf("alloc fail\n");
        return 1;
    }

    for (int epoch = 0; epoch < 800; epoch++)
    {
        float64_t loss_sum = 0.0;
        for (size_t cls = 0; cls < 2; cls++)
        {
            for (size_t i = 0; i < per_class; i++)
            {
                const float64_t r = (float64_t) i / (float64_t) per_class * 1.8;
                const float64_t t = 1.75 * r + (cls == 0 ? 0.0 : M_PI);
                const float64_t noise = ((float64_t)rand() / RAND_MAX - 0.5) * 0.2;

                x->data[0] = r * cos(t) + noise;
                x->data[1] = r * sin(t) + noise;

                dense_forward(l1, x, h);
                tanh_inplace(h);

                dense_forward(l2, h, y);
                sigmoid_inplace(y);

                target->data[0] = (float64_t) cls;
                loss_sum += mse_loss(y, target);

                mse_grad(y, target, grad_out);

                struct float_matrix *dW2 = NULL;
                struct float_array *db2 = NULL;
                struct float_array *d_h = create_float_array(32);

                dense_backward(l2, h, grad_out, &dW2, &db2, d_h);
                sgd_update_dense(l2, dW2, db2, 0.05);
                free_float_matrix(&dW2); free_float_array(&db2);

                struct float_matrix *dW1 = NULL;
                struct float_array *db1 = NULL;
                struct float_array *d_x = create_float_array(in_dim);
                dense_backward(l1, x, d_h, &dW1, &db1, d_x);

                sgd_update_dense(l1, dW1, db1, 0.05);

                free_float_matrix(&dW1);
                free_float_array(&db1);
                free_float_array(&d_h);
                free_float_array(&d_x);
            }
        }
        if (epoch % 200 == 0)
        {
            printf("epoch %d loss=%.6f\n", epoch, loss_sum / (float64_t) N);
        }

    }

    for (int s = 0; s < 8; s++)
    {
        const float64_t r = (float64_t) s / 8.0 * 1.8;
        const float64_t t = 1.75 * r;

        x->data[0] = r * cos(t);
        x->data[1] = r * sin(t);

        dense_forward(l1, x, h);
        tanh_inplace(h);

        dense_forward(l2, h, y);
        sigmoid_inplace(y);

        printf("pt (%.3f, %.3f) -> %.3f\n", x->data[0], x->data[1], y->data[0]);
    }

    dense_free(&l1);
    dense_free(&l2);

    free_float_array(&x);
    free_float_array(&h);
    free_float_array(&y);
    free_float_array(&target);
    free_float_array(&grad_out);

    return 0;
}
