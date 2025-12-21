#include "dropout.h"
#include <stdlib.h>
#include <time.h>

struct dropout_layer *dropout_create(double p)
{
    if (p < 0.0 || p >= 1.0)
    {
        return NULL;
    }
    struct dropout_layer *l = malloc(sizeof(*l));
    if (!l)
    {
        return NULL;
    }

    l->p = p;
    l->mask = NULL;
    
    return l;
}

void dropout_free(struct dropout_layer **layer)
{
    if (!layer || !*layer)
    {
        return;
    }
    struct dropout_layer *l = *layer;
    if (l->mask)
    {
        free_float_array(&l->mask);
    }
    free(l);
    *layer = NULL;
}

int dropout_forward(struct dropout_layer *layer, const struct float_array *input, struct float_array *output, int training)
{
    if (!layer || !input || !output)
    {
        return -1;
    }
    if (input->size != output->size)
    {
        return -1;
    }

    if (!layer->mask)
    {
        layer->mask = create_float_array(input->size);
        if (!layer->mask)
        {
            return -1;
        }
    }

    if (training)
    {
        const double keep = 1.0 - layer->p;
        for (size_t i = 0; i < input->size; i++)
        {
            const double r = (double)rand() / RAND_MAX;
            const double m = (r < keep) ? (1.0 / keep) : 0.0; 

            layer->mask->data[i] = m;
            output->data[i] = input->data[i] * m;
        }
    }
    else
    {
        for (size_t i = 0; i < input->size; i++)
        {
            layer->mask->data[i] = 1.0;
            output->data[i] = input->data[i];
        }
    }
    return 0;
}

int dropout_backward(const struct dropout_layer *layer, 
    const struct float_array *d_output, struct float_array *d_input)
{
    if (!layer || !d_output || !d_input || !layer->mask)
    {
        return -1;
    }
    if (d_output->size != d_input->size || d_output->size != layer->mask->size)
    {
        return -1;
    }

    for (size_t i = 0; i < d_output->size; i++)
    {
        d_input->data[i] = d_output->data[i] * layer->mask->data[i];
    }
    return 0;
}
