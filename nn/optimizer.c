#include "optimizer.h"

int sgd_update_dense(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db, const double lr)
{
    return dense_apply_sgd_update(layer, dW, db, lr);
}

int adam_update_dense(struct dense_layer *layer, const struct float_matrix *dW, const struct float_array *db,
                      const double lr, const double beta1, const double beta2, const double eps)
{
    return dense_apply_adam_update(layer, dW, db, lr, beta1, beta2, eps);
}
