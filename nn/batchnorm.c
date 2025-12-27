#include "batchnorm.h"
#include <stdlib.h>
#include <math.h>

struct batchnorm_layer *batchnorm_create(const size_t dim)
{
    struct batchnorm_layer *l = malloc(sizeof(*l));
    if (!l)
    {
        return NULL;
    }

    l->dim = dim;

    l->gamma = create_float_array(dim);
    l->beta = create_float_array(dim);
    l->mg = create_float_array(dim);
    l->vg = create_float_array(dim);
    l->mb = create_float_array(dim);
    l->vb = create_float_array(dim);
    l->last_xhat = create_float_array(dim);

    l->adam_t = 0;
    l->eps = 1e-5;

    if (!l->gamma || !l->beta || !l->mg || !l->vg || !l->mb || !l->vb || !l->last_xhat)
    {
        batchnorm_free(&l);
        return NULL;
    }

    for (size_t i = 0; i < dim; i++)
    {
        l->gamma->data[i] = 1.0;
        l->beta->data[i] = 0.0;
        l->mg->data[i] = 0.0;
        l->vg->data[i] = 0.0;
        l->mb->data[i] = 0.0;
        l->vb->data[i] = 0.0;
        l->last_xhat->data[i] = 0.0;
    }

    l->last_var = 1.0;
    return l;
}

void batchnorm_free(struct batchnorm_layer **layer)
{
    if (!layer || !*layer)
    {
        return;
    }

    struct batchnorm_layer *l = *layer;

    free_float_array(&l->gamma);
    free_float_array(&l->beta);
    free_float_array(&l->mg);
    free_float_array(&l->vg);
    free_float_array(&l->mb);
    free_float_array(&l->vb);
    free_float_array(&l->last_xhat);

    free(l);
    *layer = NULL;
}


int batchnorm_forward(const struct batchnorm_layer *layer, const struct float_array *input, struct float_array *output)
{
    if (!layer || !input || !output)
    {
        return -1;
    }

    if (input->size != layer->dim || output->size != layer->dim)
    {
        return -1;
    }

    float64_t mean = 0.0;
    for (size_t i = 0; i < layer->dim; i++)
    {
        mean += input->data[i];
    }
    mean /= (float64_t)layer->dim;

    float64_t var = 0.0;
    for (size_t i = 0; i < layer->dim; i++)
    {
        const float64_t d = input->data[i] - mean;
        var += d * d;
    }
    var /= (float64_t)layer->dim;

    const float64_t denom = sqrt(var + layer->eps);
    for (size_t i = 0; i < layer->dim; i++)
    {
        const float64_t xhat = (input->data[i] - mean) / denom;
        layer->last_xhat->data[i] = xhat;
        output->data[i] = layer->gamma->data[i] * xhat + layer->beta->data[i];
    }

    ((struct batchnorm_layer *)layer)->last_var = var;

    return 0;
}

int batchnorm_backward(const struct batchnorm_layer *layer, const struct float_array *d_out,
                       const struct float_array *d_input, struct float_array **d_gamma_out, struct float_array **d_beta_out)
{
    if (!layer || !d_out)
    {
        return -1;
    }

    const size_t dim = layer->dim;
    if (d_out->size != dim)
    {
        return -1;
    }

    struct float_array *d_gamma = create_float_array(dim);
    struct float_array *d_beta = create_float_array(dim);

    if (!d_gamma || !d_beta)
    {
        free_float_array(&d_gamma);
        free_float_array(&d_beta);
        return -1;
    }

    for (size_t i = 0; i < dim; i++)
    {
        d_gamma->data[i] = d_out->data[i] * layer->last_xhat->data[i];
        d_beta->data[i] = d_out->data[i];
    }

    if (d_input)
    {
        if (d_input->size != dim)
        {
            free_float_array(&d_gamma);
            free_float_array(&d_beta);
            return -1;
        }

        double var = layer->last_var;
        double denom = sqrt(var + layer->eps);

        double mean_dout = 0.0;
        double mean_dout_xhat = 0.0;
        for (size_t i = 0; i < dim; i++)
        {
            mean_dout += d_out->data[i] * layer->gamma->data[i] / denom;
            mean_dout_xhat += d_out->data[i] * layer->gamma->data[i] * layer->last_xhat->data[i] / denom;
        }
        mean_dout /= (double)dim;
        mean_dout_xhat /= (double)dim;

        for (size_t i = 0; i < dim; i++)
        {
            double term = (d_out->data[i] * layer->gamma->data[i] / denom) - mean_dout - layer->last_xhat->data[i] * mean_dout_xhat;
            d_input->data[i] = term;
        }
    }

    *d_gamma_out = d_gamma;
    *d_beta_out = d_beta;
    return 0;
}

int batchnorm_apply_adam_update(struct batchnorm_layer *layer, const struct float_array *d_gamma, const struct float_array *d_beta,
                                double lr, double beta1, double beta2, double eps)
{
    if (!layer || !d_gamma || !d_beta) return -1;
    if (d_gamma->size != layer->dim || d_beta->size != layer->dim) return -1;

    layer->adam_t += 1;
    double bc1 = 1.0 - pow(beta1, (double)layer->adam_t);
    double bc2 = 1.0 - pow(beta2, (double)layer->adam_t);

    for (size_t i = 0; i < layer->dim; i++)
    {
        double g = d_gamma->data[i];
        layer->mg->data[i] = beta1 * layer->mg->data[i] + (1.0 - beta1) * g;
        layer->vg->data[i] = beta2 * layer->vg->data[i] + (1.0 - beta2) * g * g;
        double mhat = layer->mg->data[i] / bc1;
        double vhat = layer->vg->data[i] / bc2;
        layer->gamma->data[i] -= lr * mhat / (sqrt(vhat) + eps);

        double gb = d_beta->data[i];
        layer->mb->data[i] = beta1 * layer->mb->data[i] + (1.0 - beta1) * gb;
        layer->vb->data[i] = beta2 * layer->vb->data[i] + (1.0 - beta2) * gb * gb;
        double mhatb = layer->mb->data[i] / bc1;
        double vhatb = layer->vb->data[i] / bc2;
        layer->beta->data[i] -= lr * mhatb / (sqrt(vhatb) + eps);
    }
    return 0;
}
