#include "dense.h"

#include <stdio.h>
#include <tgmath.h>
#include "matrix/matrix_math.h"

struct dense_layer *dense_create(const size_t in_dim, const size_t out_dim)
{
    struct dense_layer *l = malloc(sizeof(*l));
    if (!l)
    {
        return NULL;
    }

    l->in_dim = in_dim;
    l->out_dim = out_dim;

    l->W = create_float_matrix(out_dim, in_dim);

    if (!l->W)
    {
        free(l);
        return NULL;
    }

    l->b = create_float_array(out_dim);
    if (!l->b)
    {
        free_float_matrix(&l->W);
        free(l);
        return NULL;
    }

    l->mW = create_float_matrix(out_dim, in_dim);
    l->vW = create_float_matrix(out_dim, in_dim);

    l->mb = create_float_array(out_dim);
    l->vb = create_float_array(out_dim);

    if (!l->mW || !l->vW || !l->mb || !l->vb)
    {
        free_float_matrix(&l->W);
        free_float_array(&l->b);
        free_float_matrix(&l->mW);
        free_float_matrix(&l->vW);
        free_float_array(&l->mb);
        free_float_array(&l->vb);
        free(l);

        return NULL;
    }
    l->adam_t = 0;

    return l;
}

void dense_free(struct dense_layer **layer)
{
    if (!layer || !*layer)
    {
        return;
    }

    struct dense_layer *l = *layer;

    free_float_matrix(&l->W);
    free_float_array(&l->b);
    free_float_matrix(&l->mW);
    free_float_matrix(&l->vW);
    free_float_array(&l->mb);
    free_float_array(&l->vb);

    free(l);
    *layer = NULL;
}

int dense_forward(const struct dense_layer *layer, const struct float_array *input, struct float_array *output)
{
    if (!layer || !input || !output)
    {
        return -1;
    }
    if (input->size != layer->in_dim || output->size != layer->out_dim)
    {
        return -1;
    }
    if (matvec_float(layer->W, input, output) != 0)
    {
        return -1;
    }

    for (size_t i = 0; i < output->size; i++)
    {
        output->data[i] += layer->b->data[i];
    }

    return 0;
}

static struct float_matrix *outer_product(const struct float_array *a, const struct float_array *b)
{
    struct float_matrix *M = create_float_matrix(a->size, b->size);
    if (!M)
    {
        return NULL;
    }
    for (size_t i = 0; i < a->size; i++)
    {
        for (size_t j = 0; j < b->size; j++)
        {
            M->data[i][j] = a->data[i] * b->data[j];
        }
    }
    return M;
}

int dense_backward(const struct dense_layer *layer,
                   const struct float_array *input,
                   const struct float_array *d_output,
                   struct float_matrix **dW_out,
                   struct float_array **db_out,
                   struct float_array *d_input)
{
    if (!layer || !input || !d_output)
    {
        fprintf(stderr, "dense_backward: NULL argument layer=%p input=%p d_output=%p\n", (void*)layer, (void*)input, (void*)d_output);
        return -1;
    }

    fprintf(stderr, "dense_backward: enter layer=%p in_dim=%zu out_dim=%zu input=%p d_output=%p\n",
            (void*)layer, layer->in_dim, layer->out_dim, (void*)input, (void*)d_output);
    if (input->size != layer->in_dim || d_output->size != layer->out_dim)
    {
        fprintf(stderr, "dense_backward: size mismatch input->size=%zu layer->in_dim=%zu d_output->size=%zu layer->out_dim=%zu\n",
                input->size, layer->in_dim, d_output->size, layer->out_dim);
        return -1;
    }

    if (!layer->W || !layer->W->data)
    {
        fprintf(stderr, "dense_backward: layer->W is NULL\n");
        return -1;
    }

    struct float_matrix *dW = outer_product(d_output, input);
    if (!dW)
    {
        fprintf(stderr, "dense_backward: outer_product failed (dW NULL)\n");
        return -1;
    }
    fprintf(stderr, "dense_backward: dW allocated rows=%zu cols=%zu\n", dW->rows, dW->cols);

    struct float_array *db = copy_float_array(d_output);
    if (!db)
    {
        free_float_matrix(&dW);
        fprintf(stderr, "dense_backward: copy_float_array failed (db NULL)\n");
        return -1;
    }
    fprintf(stderr, "dense_backward: db allocated size=%zu\n", db->size);

    if (d_input)
    {
        if (d_input->size != layer->in_dim)
        {
            fprintf(stderr, "dense_backward: d_input size mismatch %zu vs %zu\n", d_input->size, layer->in_dim);
            free_float_matrix(&dW);
            free_float_array(&db);

            return -1;
        }
        fprintf(stderr, "dense_backward: calling matvec_transpose_float\n");
        if (matvec_transpose_float(layer->W, d_output, d_input) != 0)
        {
            fprintf(stderr, "dense_backward: matvec_transpose_float failed\n");
            free_float_matrix(&dW);
            free_float_array(&db);

            return -1;
        }
        fprintf(stderr, "dense_backward: matvec_transpose_float ok\n");
    }

    *dW_out = dW;
    *db_out = db;
    return 0;
}

int dense_apply_sgd_update(struct dense_layer *layer, const struct float_matrix *dW,
    const struct float_array *db, const double lr)
{
    if (!layer || !dW || !db)
    {
        return -1;
    }
    if (dW->rows != layer->out_dim || dW->cols != layer->in_dim)
    {
        return -1;
    }
    if (db->size != layer->out_dim)
    {
        return -1;
    }

    for (size_t i = 0; i < layer->out_dim; i++)
    {
        for (size_t j = 0; j < layer->in_dim; j++)
        {
            layer->W->data[i][j] -= lr * dW->data[i][j];
        }
        layer->b->data[i] -= lr * db->data[i];
    }
    return 0;
}

int dense_apply_adam_update(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db,
                            const double lr, double beta1, double beta2, double eps)
{
    if (!layer || !dW || !db)
    {
        return -1;
    }
    if (dW->rows != layer->out_dim || dW->cols != layer->in_dim)
    {
        return -1;
    }
    if (db->size != layer->out_dim)
    {
        return -1;
    }

    layer->adam_t += 1;

    const double bias_correction1 = 1.0 - pow(beta1, (double)layer->adam_t);
    const double bias_correction2 = 1.0 - pow(beta2, (double)layer->adam_t);

    for (size_t i = 0; i < layer->out_dim; i++)
    {
        for (size_t j = 0; j < layer->in_dim; j++)
        {
            const double g = dW->data[i][j];
            layer->mW->data[i][j] = beta1 * layer->mW->data[i][j] + (1.0 - beta1) * g;
            layer->vW->data[i][j] = beta2 * layer->vW->data[i][j] + (1.0 - beta2) * g * g;

            const double m_hat = layer->mW->data[i][j] / bias_correction1;
            const double v_hat = layer->vW->data[i][j] / bias_correction2;

            layer->W->data[i][j] -= lr * m_hat / (sqrt(v_hat) + eps);
        }

        const double gb = db->data[i];

        layer->mb->data[i] = beta1 * layer->mb->data[i] + (1.0 - beta1) * gb;
        layer->vb->data[i] = beta2 * layer->vb->data[i] + (1.0 - beta2) * gb * gb;

        const double m_hat_b = layer->mb->data[i] / bias_correction1;
        const double v_hat_b = layer->vb->data[i] / bias_correction2;

        layer->b->data[i] -= lr * m_hat_b / (sqrt(v_hat_b) + eps);
    }
    return 0;
}
