#include "loss.h"

float64_t mse_loss(const struct float_array *pred, const struct float_array *target)
{
    if (!pred || !target || !pred->data || !target->data)
    {
        return 0.0;
    }
    if (pred->size != target->size)
    {
        return 0.0;
    }
    float64_t sum = 0.0;
    for (size_t i = 0; i < pred->size; i++)
    {
        const double d = pred->data[i] - target->data[i];
        sum += d * d;
    }
    return sum / (float64_t) pred->size;
}

int mse_grad(const struct float_array *pred, const struct float_array *target, struct float_array *grad_out)
{
    if (!pred || !target || !grad_out)
    {
        return -1;
    }
    if (pred->size != target->size || pred->size != grad_out->size)
    {
        return -1;
    }
    for (size_t i = 0; i < pred->size; i++)
    {
        grad_out->data[i] = 2.0 * (pred->data[i] - target->data[i]) / (float64_t) pred->size;
    }
    return 0;
}

float64_t cross_entropy_loss_from_probs(const struct float_array *probs, const size_t label_index)
{
    if (!probs || !probs->data || label_index >= probs->size)
    {
        return 0.0;
    }
    double p = probs->data[label_index];
    if (p <= 0.0)
    {
        p = 1e-15;
    }
    return -log(p);
}

int cross_entropy_grad_from_probs(const struct float_array *probs, const size_t label_index, struct float_array *grad_out)
{
    if (!probs || !grad_out || !probs->data || !grad_out->data)
    {
        return -1;
    }
    if (probs->size != grad_out->size)
    {
        return -1;
    }
    for (size_t i = 0; i < probs->size; i++)
    {
        grad_out->data[i] = probs->data[i];
    }
    if (label_index >= probs->size)
    {
        return -1;
    }
    grad_out->data[label_index] -= 1.0;
    return 0;
}
