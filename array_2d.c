#include "array_2d.h"

void destroy_array_2d(size_t ***ptr, const size_t height)
{
    if (ptr == NULL || height == 0)
    {
        return;
    }

    size_t **temp = *ptr;
    for (size_t i = 0; i < height; i++)
    {
        free(*(temp + i));
    }
    free(temp);

    *ptr = NULL;
}

int create_array_2d(size_t ***ptr, const size_t width, const size_t height)
{
    if(width == 0 || height == 0 || ptr == NULL)
    {
        return 1;
    }

    size_t **array = malloc(sizeof(size_t *) * height);
    if(array == NULL)
    {
        return 2;
    }

    for(size_t i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(size_t) * width);
        if(*(array + i) == NULL)
        {
            destroy_array_2d(&array, i);
            return 2;
        }
    }

    *ptr = array;

    return 0;
}

void display_array_2d(size_t **ptr, const size_t width, const size_t height)
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