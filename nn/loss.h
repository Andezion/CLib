#pragma once

#include "array/array.h"

float64_t mse_loss(const struct float_array *pred, const struct float_array *target);
int mse_grad(const struct float_array *pred, const struct float_array *target, struct float_array *grad_out);

float64_t cross_entropy_loss_from_probs(const struct float_array *probs, size_t label_index);
int cross_entropy_grad_from_probs(const struct float_array *probs, size_t label_index, struct float_array *grad_out);
