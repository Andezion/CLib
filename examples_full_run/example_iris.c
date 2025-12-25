#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "array/array.h"

int main(void)
{
    srand(1);

    const size_t n_classes = 3;
    const size_t per_class = 50;
    const size_t N = n_classes * per_class;
    const size_t in_dim = 4;

    double centers[3][4] = {{5.1,3.5,1.4,0.2},{5.9,3.0,4.2,1.5},{6.3,3.3,6.0,2.5}};

    struct float_array *x = create_float_array(in_dim);
    struct float_array *h = create_float_array(16);
    struct float_array *y = create_float_array(n_classes);
    struct float_array *grad_out = create_float_array(n_classes);

    struct dense_layer *l1 = dense_create(in_dim, 16);
    struct dense_layer *l2 = dense_create(16, n_classes);

    if (!x || !h || !y || !grad_out || !l1 || !l2)
    {
        printf("alloc fail\n");
        return 1;
    }

    for (int epoch = 0; epoch < 500; epoch++)
    {
        double loss_sum = 0.0;
        for (size_t cls = 0; cls < n_classes; cls++)
        {
            for (size_t i = 0; i < per_class; i++)
            {

                for (size_t d = 0; d < in_dim; d++)
                {
                    double noise = ((double)rand() / RAND_MAX - 0.5) * 0.6;
                    x->data[d] = centers[cls][d] + noise;
                }

                // forward
                dense_forward(l1, x, h); tanh_inplace(h);
                dense_forward(l2, h, y); softmax_inplace(y);

                loss_sum += cross_entropy_loss_from_probs(y, cls);

                cross_entropy_grad_from_probs(y, cls, grad_out);

                struct float_matrix *dW2 = NULL;
                struct float_array *db2 = NULL;
                struct float_array *d_h = create_float_array(16);

                dense_backward(l2, h, grad_out, &dW2, &db2, d_h);
                sgd_update_dense(l2, dW2, db2, 0.01);
                free_float_matrix(&dW2); free_float_array(&db2);

                struct float_matrix *dW1 = NULL;
                struct float_array *db1 = NULL;
                struct float_array *d_x = create_float_array(in_dim);

                dense_backward(l1, x, d_h, &dW1, &db1, d_x);
                sgd_update_dense(l1, dW1, db1, 0.01);

                free_float_matrix(&dW1); free_float_array(&db1);
                free_float_array(&d_h); free_float_array(&d_x);
            }
        }

        if (epoch % 100 == 0)
        {
            printf("epoch %d loss=%.6f\n", epoch, loss_sum / (double)N);
        }
    }

    for (size_t cls = 0; cls < n_classes; cls++)
    {
        for (size_t t = 0; t < 3; t++)
        {
            for (size_t d = 0; d < in_dim; d++)
            {
                double noise = ((double)rand() / RAND_MAX - 0.5) * 0.6;
                x->data[d] = centers[cls][d] + noise;
            }
            dense_forward(l1, x, h); tanh_inplace(h);
            dense_forward(l2, h, y); softmax_inplace(y);

            size_t pred = 0; double best = y->data[0];
            for (size_t k = 1; k < n_classes; k++) if (y->data[k] > best) { best = y->data[k]; pred = k; }

            printf("true=%zu pred=%zu probs=[", cls, pred);
            for (size_t k = 0; k < n_classes; k++) printf(" %.3f", y->data[k]);
            printf(" ]\n");
        }
    }

    dense_free(&l1); dense_free(&l2);
    free_float_array(&x); free_float_array(&h); free_float_array(&y); free_float_array(&grad_out);

    return 0;
}
