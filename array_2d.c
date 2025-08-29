#include "array_2d.h"

void destroy_array_i_2d(int64_t ***ptr, const size_t height)
{
    if (ptr == NULL || height == 0)
    {
        return;
    }

    int64_t **temp = *ptr;
    for (size_t i = 0; i < height; i++)
    {
        free(*(temp + i));
    }
    free(temp);

    *ptr = NULL;
}
void destroy_array_f_2d(float64_t ***ptr, const size_t height)
{
    if (ptr == NULL || height == 0)
    {
        return;
    }

    float64_t **temp = *ptr;
    for (size_t i = 0; i < height; i++)
    {
        free(*(temp + i));
    }
    free(temp);

    *ptr = NULL;
}

int create_array_i_2d_rect(int64_t ***ptr, const size_t width, const size_t height)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    int64_t **array = malloc(sizeof(int64_t *) * height);
    if(array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(int64_t) * width);
        if(*(array + i) == NULL)
        {
            destroy_array_i_2d(&array, i);
            return 2;
        }
    }

    *ptr = array;

    return 0;
}
int create_array_i_2d_init_rect(int64_t ***ptr, const size_t width, const size_t height, const int64_t value)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    int64_t **array = malloc(sizeof(int64_t *) * height);
    if(array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(int64_t) * width);
        if(*(array + i) == NULL)
        {
            destroy_array_i_2d(&array, i);
            return 2;
        }
    }

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            *(*(array + 1) + j) = value;
        }
    }

    *ptr = array;

    return 0;
}
int create_array_i_2d_square(int64_t ***ptr, const size_t size)
{
    if(size == 0 || ptr == NULL)
    {
        return 1;
    }

    int64_t **array = malloc(sizeof(int64_t *) * size);
    if (array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < size; i++)
    {
        *(array + i) = malloc(sizeof(int64_t) * size);
        if (*(array + i) == NULL)
        {
            destroy_array_i_2d(&array, i);
            return 2;
        }
    }

    *ptr = array;

    return 0;
}
int create_array_i_2d_init_square(int64_t ***ptr, const size_t size, const int64_t value)
{
    if(size == 0 || ptr == NULL)
    {
        return 1;
    }

    int64_t **array = malloc(sizeof(int64_t *) * size);
    if (array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < size; i++)
    {
        *(array + i) = malloc(sizeof(int64_t) * size);
        if (*(array + i) == NULL)
        {
            destroy_array_i_2d(&array, i);
            return 2;
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            *(*(array + i) + j) = value;
        }
    }

    *ptr = array;

    return 0;
}

int create_array_f_2d_rect(float64_t ***ptr, const size_t width, const size_t height)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    float64_t **array = malloc(sizeof(float64_t *) * height);
    if (array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(float64_t) * width);
        if (*(array + i) == NULL)
        {
            destroy_array_f_2d(&array, i);
            return 2;
        }
    }
    *ptr = array;
    return 0;
}

void display_array_i_2d(int64_t **ptr, const size_t width, const size_t height)
{
    if (ptr == NULL || width == 0 || height == 0)
    {
        return;
    }

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            printf("%" PRId64 " ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}
void display_array_f_2d(float64_t **ptr, const size_t width, const size_t height)
{
    if (ptr == NULL || width == 0 || height == 0)
    {
        return;
    }

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            printf("%f ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}
