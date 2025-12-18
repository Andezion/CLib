#include "dense.h"
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
        return -1;
    }
    if (input->size != layer->in_dim || d_output->size != layer->out_dim)
    {
        return -1;
    }

    struct float_matrix *dW = outer_product(d_output, input);
    if (!dW)
    {
        return -1;
    }

    struct float_array *db = copy_float_array(d_output);
    if (!db)
    {
        free_float_matrix(&dW);
        return -1;
    }

    if (d_input)
    {
        if (d_input->size != layer->in_dim)
        {
            free_float_matrix(&dW);
            free_float_array(&db);
            return -1;
        }
        if (matvec_transpose_float(layer->W, d_output, d_input) != 0)
        {
            free_float_matrix(&dW);
            free_float_array(&db);
            return -1;
        }
    }

    *dW_out = dW;
    *db_out = db;
    return 0;
}

int dense_apply_sgd_update(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db, const double lr)
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
