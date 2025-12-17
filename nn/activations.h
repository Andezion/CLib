#pragma once

#include "array/array.h"

typedef int (*act_fn)(struct float_array *);

typedef int (*act_grad_fn)(const struct float_array *y, struct float_array *grad_out);

int relu_inplace(struct float_array *x);
int relu_grad(const struct float_array *y, struct float_array *grad_out);

int sigmoid_inplace(struct float_array *x);
int sigmoid_grad(const struct float_array *y, struct float_array *grad_out);

int tanh_inplace(struct float_array *x);
int tanh_grad(const struct float_array *y, struct float_array *grad_out);

int softmax_inplace(struct float_array *x);
int softmax_grad(const struct float_array *y, struct float_array *grad_out);
