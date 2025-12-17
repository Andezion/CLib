#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dense.h"
#include "activations.h"
#include "loss.h"
#include "optimizer.h"

int main(void)
{
    srand(time(NULL));

    const size_t in_dim = 4;
    const size_t out_dim = 3;

    struct dense_layer *model = dense_create(in_dim, out_dim);
    if (!model)
    {
        printf("failed create\n");
        return 1;
    }

    for (size_t i = 0; i < model->W->rows; i++)
    {
        for (size_t j = 0; j < model->W->cols; j++)
        {
            model->W->data[i][j] = ((float64_t) rand() / RAND_MAX - 0.5) * 0.1;
        }
    }
    for (size_t i = 0; i < model->b->size; i++)
    {
        model->b->data[i] = 0.0;
    }

    struct float_array *x = create_float_array(in_dim);
    struct float_array *logits = create_float_array(out_dim);
    struct float_array *probs = create_float_array(out_dim);
    struct float_array *grad_out = create_float_array(out_dim);

    for (size_t i = 0; i < in_dim; i++)
    {
        x->data[i] = (float64_t) rand() / RAND_MAX;
    }

    for (int epoch = 0; epoch < 200; epoch++)
    {
        const double lr = 1.0;
        const size_t label = 1;

        dense_forward(model, x, logits);

        for (size_t i = 0; i < out_dim; i++)
        {
            probs->data[i] = logits->data[i];
        }
        softmax_inplace(probs);

        const double loss = cross_entropy_loss_from_probs(probs, label);

        cross_entropy_grad_from_probs(probs, label, grad_out);

        struct float_matrix *dW = NULL;
        struct float_array *db = NULL;

        struct float_array *d_input = create_float_array(in_dim);
        if (!d_input)
        {
            break;
        }
        dense_backward(model, x, grad_out, &dW, &db, d_input);

        sgd_update_dense(model, dW, db, lr);

        free_float_matrix(&dW);
        free_float_array(&db);
        free_float_array(&d_input);

        if (epoch % 20 == 0)
        {
            printf("epoch %d loss=%.6f\n", epoch, loss);
        }
    }

    dense_free(&model);
    free_float_array(&x);
    free_float_array(&logits);
    free_float_array(&probs);
    free_float_array(&grad_out);

    return 0;
}
