#pragma once

#include "dense.h"
#include "matrix/matrix.h"
#include "array/array.h"


int sgd_update_dense(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db, double lr);
int adam_update_dense(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db,
					  double lr, double beta1, double beta2, double eps);
