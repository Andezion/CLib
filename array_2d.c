#include "array_2d.h"

void destroy_array_2d(signed long long int ***ptr, const size_t height)
{
    if (ptr == NULL || height == 0)
    {
        return;
    }

    signed long long int **temp = *ptr;
    for (size_t i = 0; i < height; i++)
    {
        free(*(temp + i));
    }
    free(temp);

    *ptr = NULL;
}

int create_array_2d(signed long long int ***ptr, const size_t width, const size_t height)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    signed long long int **array = malloc(sizeof(signed long long int *) * height);
    if(array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(signed long long int) * width);
        if(*(array + i) == NULL)
        {
            destroy_array_2d(&array, i);
            return 2;
        }
    }

    *ptr = array;

    return 0;
}

int create_array_2d_init(signed long long int ***ptr, const size_t width, const size_t height, const signed long long int value)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    signed long long int **array = malloc(sizeof(signed long long int *) * height);
    if(array == NULL)
    {
        return 2;
    }

    for(signed long long int i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(signed long long int) * width);
        if(*(array + i) == NULL)
        {
            destroy_array_2d(&array, i);
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

int create_array_2d(signed long long int ***ptr, const size_t size)
{
    if(size == 0 || ptr == NULL)
    {
        return 1;
    }

    signed long long int **array = malloc(sizeof(signed long long int *) * size);
    if (array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < size; i++)
    {
        *(array + i) = malloc(sizeof(signed long long int) * size);
        if (*(array + i) == NULL)
        {
            destroy_array_2d(&array, i);
            return 2;
        }
    }

    *ptr = array;

    return 0;
}

int create_array_2d_init(signed long long int ***ptr, const size_t size, const signed long long int value)
{
    if(size == 0 || ptr == NULL)
    {
        return 1;
    }

    signed long long int **array = malloc(sizeof(signed long long int *) * size);
    if (array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < size; i++)
    {
        *(array + i) = malloc(sizeof(signed long long int) * size);
        if (*(array + i) == NULL)
        {
            destroy_array_2d(&array, i);
            return 2;
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            *(*(array + 1) + j) = value;
        }
    }

    *ptr = array;

    return 0;
}

void display_array_2d(signed long long int **ptr, const size_t width, const size_t height)
{
    if (ptr == NULL || width == 0 || height == 0)
    {
        return;
    }

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            printf("%zu ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}
