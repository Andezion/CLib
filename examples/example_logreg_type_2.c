#include <stdio.h>
#include <stdlib.h>

#include "../nn/dense.h"
#include "../nn/activations.h"
#include "../nn/loss.h"
#include "../matrix/matrix.h"
#include "../array/array.h"

int main(void)
{
    const size_t in_dim = 2;
    const size_t out_dim = 1;
    struct dense_layer *model = dense_create(in_dim, out_dim);
    if (!model)
    {
        fprintf(stderr, "Failed to create dense layer\n");
        return 1;
    }

    initialization_random_float_matrix(model->W, -1.0, 1.0);
    initialization_random_float_array(model->b, -1.0, 1.0);

    const double X[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    const double Y[4] = {0.0, 0.0, 0.0, 1.0};
    const size_t N = 4;

    const size_t epochs = 5000;

    struct float_array *x = create_float_array(in_dim);
    struct float_array *out = create_float_array(out_dim);
    struct float_array *target = create_float_array(out_dim);
    struct float_array *dout = create_float_array(out_dim);

    if (!x || !out || !target || !dout)
    {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    for (size_t e = 0; e < epochs; e++)
    {
        double epoch_loss = 0.0;
        for (size_t i = 0; i < N; i++)
        {
            const double lr = 0.5;
            for (size_t j = 0; j < in_dim; j++)
            {
                x->data[j] = X[i][j];
            }

            if (dense_forward(model, x, out) != 0)
            {
                fprintf(stderr, "Forward failed\n");
                return 1;
            }
            if (sigmoid_inplace(out) != 0)
            {
                fprintf(stderr, "Sigmoid failed\n");
                return 1;
            }

            target->data[0] = Y[i];
            epoch_loss += mse_loss(out, target);

            if (mse_grad(out, target, dout) != 0)
            {
                fprintf(stderr, "mse_grad failed\n");
                return 1;
            }

            struct float_matrix *dW = NULL;
            struct float_array *db = NULL;
            if (dense_backward(model, x, dout, &dW, &db, NULL) != 0)
            {
                fprintf(stderr, "Backward failed\n");
                return 1;
            }

            if (dense_apply_sgd_update(model, dW, db, lr) != 0)
            {
                fprintf(stderr, "Update failed\n");
                return 1;
            }

            free_float_matrix(&dW);
            free_float_array(&db);
        }

        if (e % 500 == 0)
        {
            printf("Epoch %zu loss: %f\n", e, epoch_loss / (double)N);
        }
    }

    printf("\nTrained model predictions:\n");
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < in_dim; j++)
        {
            x->data[j] = X[i][j];
        }

        dense_forward(model, x, out);
        sigmoid_inplace(out);
        printf("x = [%g, %g] -> pred = %g, label = %g\n", X[i][0], X[i][1], out->data[0], Y[i]);
    }

    free_float_array(&x);
    free_float_array(&out);
    free_float_array(&target);
    free_float_array(&dout);
    dense_free(&model);

    return 0;
}
