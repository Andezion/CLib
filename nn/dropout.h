#pragma once

#include "array/array.h"

struct dropout_layer
{
    double p;
    struct float_array *mask; 
};

struct dropout_layer *dropout_create(double p);
void dropout_free(struct dropout_layer **layer);

int dropout_forward(struct dropout_layer *layer, const struct float_array *input, struct float_array *output, int training);
int dropout_backward(const struct dropout_layer *layer, const struct float_array *d_output, struct float_array *d_input);
