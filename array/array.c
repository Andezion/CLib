#include "array.h"
#include <inttypes.h>
#include <stdio.h>

void destroy_int_array(struct int_array **array)
{
    if (array == NULL || *array == NULL)
    {
        return;
    }

    struct int_array *temp = *array;
    if (temp->data != NULL)
    {
        free(temp->data);
    }
    free(temp);
    *array = NULL;
}
void destroy_float_array(struct float_array **array)
{
    if (array == NULL || *array == NULL)
    {
        return;
    }

    struct float_array *temp = *array;
    if (temp->data != NULL)
    {
        free(temp->data);
    }
    free(temp);
    *array = NULL;
}

void display_int_array(const struct int_array *array)
{
    if (array == NULL || array->data == NULL || array->size == 0)
    {
        return;
    }
    for (size_t i = 0; i < array->size; i++)
    {
        printf("%" PRId64 " ", *(array->data + i));
    }
    printf("\n");
}
void display_float_array(const struct float_array *array)
{
    if (array == NULL || array->data == NULL || array->size == 0)
    {
        return;
    }
    for (size_t i = 0; i < array->size; i++)
    {
        printf("%f ", *(array->data + i));
    }
    printf("\n");
}

struct float_array * copy_float_array(const struct float_array *arr)
{
    if (arr == NULL || arr->data == NULL || arr->size == 0)
    {
        return NULL;
    }
}

struct int_array * copy_int_array(const struct int_array *arr)
{
    if (arr == NULL || arr->data == NULL || arr->size == 0)
    {
        return NULL;
    }

    struct int_array *temp = malloc(sizeof(struct int_array));
    if (temp == NULL)
    {
        return NULL;
    }

    temp->size = arr->size;
    temp->data = malloc(temp->size * sizeof(int));
    if (temp->data == NULL)
    {
        free(temp);
        return NULL;
    }

    for (size_t i = 0; i < temp->size; i++)
    {
        temp->data[i] = *(arr->data + i);
    }

    return temp;
}

struct float_array *create_float_array(const size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    struct float_array *arr = calloc(1, sizeof(struct float_array));
    if (arr == NULL)
    {
        return NULL;
    }

    arr->size = size;
    arr->data = calloc(size, sizeof(float64_t));
    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}
struct int_array *create_int_array(const size_t size)
{
    if (size <= 0)
    {
        return NULL;
    }

    struct int_array *arr = calloc(1, sizeof(struct int_array));
    if (arr == NULL)
    {
        return NULL;
    }

    arr->size = size;
    arr->data = calloc(size, sizeof(int64_t) );
    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

int initialization_float_array(const struct float_array *arr, const float64_t value)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = value;
    }
    return 0;
}

int initialization_random_int_array(const struct int_array *arr, const int64_t min, const int64_t max)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = min + rand() % (max - min + 1);
    }

    return 1;
}
int initialization_random_float_array(const struct float_array *arr, const float64_t min, const float64_t max)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = min + (max - min) * ((double)rand() / RAND_MAX);
    }

    return 1;
}

int initialization_int_array(const struct int_array *arr, const int64_t value)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = value;
    }
    return 0;
}
