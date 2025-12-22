#pragma once

#include "matrix/matrix.h"
#include "array/array.h"

struct dense_layer
{
    struct float_matrix *W;
    struct float_array *b;
    size_t in_dim;
    size_t out_dim;
    /* Adam moments */
    struct float_matrix *mW;
    struct float_matrix *vW;
    struct float_array *mb;
    struct float_array *vb;
    size_t adam_t;
};

struct dense_layer *dense_create(size_t in_dim, size_t out_dim);
void dense_free(struct dense_layer **layer);


int dense_forward(const struct dense_layer *layer, const struct float_array *input, struct float_array *output);
int dense_backward(const struct dense_layer *layer,
                   const struct float_array *input,
                   const struct float_array *d_output,
                   struct float_matrix **dW_out,
                   struct float_array **db_out,
                   struct float_array *d_input);

int dense_apply_sgd_update(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db, double lr);
int dense_apply_adam_update(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db,
                           double lr, double beta1, double beta2, double eps);
