#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../nn/optimizer.h"
#include "array/array.h"

int main(void)
{
    srand(3);
    const size_t in_dim = 2;
    const size_t h = 8;
    const size_t out_dim = 3;

    struct dense_layer *l1 = dense_create(in_dim, h);
    struct dense_layer *l2 = dense_create(h, out_dim);

    if (!l1 || !l2)
    {
        printf("alloc fail\n");
        return 1;
    }

    struct float_array *x = create_float_array(in_dim);
    struct float_array *a = create_float_array(h);
    struct float_array *logits = create_float_array(out_dim);
    struct float_array *probs = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    const size_t N = 300;

    float64_t data[N][2];
    size_t labels[N];

    for (size_t i = 0; i < N; i++)
    {
        const size_t cls = i % out_dim;
        labels[i] = cls;

        float64_t angle = (float64_t) cls * 2.0 * 3.14159265 / (float64_t) out_dim;

        data[i][0] = cos(angle) + (rand() % 100 / 500.0 - 0.1);
        data[i][1] = sin(angle) + (rand() % 100 / 500.0 - 0.1);
    }

    for (int epoch = 0; epoch < 300; epoch++)
    {
        float64_t loss = 0.0;
        size_t correct = 0;

        for (size_t i = 0; i < N; i++)
        {
            const float64_t lr = 0.02;

            x->data[0] = data[i][0];
            x->data[1] = data[i][1];

            dense_forward(l1, x, a);
            relu_inplace(a);
            dense_forward(l2, a, logits);

            for (size_t k = 0; k < out_dim; k++)
            {
                probs->data[k] = logits->data[k];
            }
            softmax_inplace(probs);

            loss += cross_entropy_loss_from_probs(probs, labels[i]);
            cross_entropy_grad_from_probs(probs, labels[i], grad_out);

            struct float_matrix *dW2 = NULL;
            struct float_array *db2 = NULL;

            struct float_array *d_a = create_float_array(h);

            dense_backward(l2, a, grad_out, &dW2, &db2, d_a);
            sgd_update_dense(l2, dW2, db2, lr);

            free_float_matrix(&dW2);
            free_float_array(&db2);

            struct float_matrix *dW1 = NULL;
            struct float_array *db1 = NULL;

            struct float_array *d_x = create_float_array(in_dim);

            dense_backward(l1, x, d_a, &dW1, &db1, d_x);
            sgd_update_dense(l1, dW1, db1, lr);

            free_float_matrix(&dW1);
            free_float_array(&db1);
            free_float_array(&d_a);
            free_float_array(&d_x);

            size_t pred = 0;
            float64_t best = probs->data[0];

            for (size_t k = 1; k < out_dim; k++)
            {
                if (probs->data[k] > best)
                {
                    best = probs->data[k];
                    pred = k;
                }
            }

            if (pred == labels[i])
            {
                correct++;
            }
        }
        if (epoch % 50 == 0)
        {
            printf("epoch %d loss=%.4f acc=%.2f%%\n", epoch,
                loss / (float64_t)N, (float64_t)correct * 100.0 / (float64_t)N);
        }
    }

    dense_free(&l1);
    dense_free(&l2);

    free_float_array(&x);
    free_float_array(&a);
    free_float_array(&logits);
    free_float_array(&probs);
    free_float_array(&grad_out);

    return 0;
}
