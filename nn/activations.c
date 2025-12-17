#include "activations.h"
#include <math.h>
#include <stdlib.h>

int relu_inplace(struct float_array *x)
{
    if (!x || !x->data)
    {
        return -1;
    }

    for (size_t i = 0; i < x->size; i++)
    {
        if (x->data[i] < 0)
        {
            x->data[i] = 0;
        }
    }

    return 0;
}
int relu_grad(const struct float_array *y, struct float_array *grad_out)
{
    if (!y || !grad_out || !y->data || !grad_out->data)
    {
        return -1;
    }
    if (y->size != grad_out->size)
    {
        return -1;
    }
    for (size_t i = 0; i < y->size; i++)
    {
        grad_out->data[i] = y->data[i] > 0 ? 1.0 : 0.0;
    }
    return 0;
}

int sigmoid_inplace(struct float_array *x)
{
    if (!x || !x->data)
    {
        return -1;
    }
    for (size_t i = 0; i < x->size; i++)
    {
        x->data[i] = 1.0 / (1.0 + exp(-x->data[i]));
    }
    return 0;
}
int sigmoid_grad(const struct float_array *y, struct float_array *grad_out)
{
    if (!y || !grad_out || !y->data || !grad_out->data)
    {
        return -1;
    }
    if (y->size != grad_out->size)
    {
        return -1;
    }
    for (size_t i = 0; i < y->size; i++)
    {
        const double s = y->data[i];
        grad_out->data[i] = s * (1.0 - s);
    }
    return 0;
}

int tanh_inplace(struct float_array *x)
{
    if (!x || !x->data)
    {
        return -1;
    }
    for (size_t i = 0; i < x->size; i++)
    {
        x->data[i] = (float64_t) tanh(x->data[i]);
    }
    return 0;
}
int tanh_grad(const struct float_array *y, struct float_array *grad_out)
{
    if (!y || !grad_out || !y->data || !grad_out->data)
    {
        return -1;
    }
    if (y->size != grad_out->size)
    {
        return -1;
    }

    for (size_t i = 0; i < y->size; i++)
    {
        const double t = y->data[i];
        grad_out->data[i] = 1.0 - t * t;
    }
    return 0;
}

int softmax_inplace(struct float_array *x)
{
    if (!x || !x->data || x->size == 0)
    {
        return -1;
    }

    float64_t maxv = x->data[0];
    for (size_t i = 1; i < x->size; i++)
    {
        if (x->data[i] > maxv)
        {
            maxv = x->data[i];
        }
    }

    float64_t sum = 0.0;
    for (size_t i = 0; i < x->size; i++)
    {
        x->data[i] = (float64_t) exp(x->data[i] - maxv);
        sum += x->data[i];
    }

    if (sum == 0.0)
    {
        return -1;
    }
    for (size_t i = 0; i < x->size; i++)
    {
        x->data[i] = x->data[i] / sum;
    }
    return 0;
}

int softmax_grad(const struct float_array *y, struct float_array *grad_out)
{
    if (!y || !grad_out || !y->data || !grad_out->data)
    {
        return -1;
    }
    if (y->size != grad_out->size)
    {
        return -1;
    }
    for (size_t i = 0; i < y->size; i++)
    {
        grad_out->data[i] = y->data[i] * (1.0 - y->data[i]);
    }
    return 0;
}
