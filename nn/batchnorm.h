#pragma once

#include "array/array.h"

struct batchnorm_layer
{
    size_t dim;

    struct float_array *gamma;
    struct float_array *beta;

    struct float_array *mg;
    struct float_array *vg;
    struct float_array *mb;
    struct float_array *vb;
    size_t adam_t;

    struct float_array *last_xhat;
    double last_var;
    double eps;
};

struct batchnorm_layer *batchnorm_create(size_t dim);
void batchnorm_free(struct batchnorm_layer **layer);

int batchnorm_forward(const struct batchnorm_layer *layer, const struct float_array *input, struct float_array *output);
int batchnorm_backward(const struct batchnorm_layer *layer, const struct float_array *d_out,
                       struct float_array *d_input, struct float_array **d_gamma_out, struct float_array **d_beta_out);

int batchnorm_apply_adam_update(struct batchnorm_layer *layer, const struct float_array *d_gamma, const struct float_array *d_beta,
                                double lr, double beta1, double beta2, double eps);
