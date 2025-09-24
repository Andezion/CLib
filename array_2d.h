#pragma once
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>

typedef double float64_t;

struct float_matrix
{
    float64_t **data;
    size_t rows;
    size_t cols;
};

struct int_matrix
{
    int32_t **data;
    size_t rows;
    size_t cols;
};

inline void free_int_matrix(struct int_matrix **matrix_to_delete)
{
    if (matrix_to_delete == NULL || *matrix_to_delete == NULL)
        return;

    struct int_matrix *matrix = *matrix_to_delete;

    if (matrix->data != NULL)
    {
        for (size_t i = 0; i < matrix->rows; i++)
        {
            free(matrix->data[i]);
        }
        free(matrix->data);
    }

    free(matrix);
    *matrix_to_delete = NULL;
}



inline struct int_matrix *create_int_matrix(const size_t rows, const size_t cols)
{
    struct int_matrix *matrix = malloc(sizeof(struct int_matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->data = calloc(rows, sizeof(int32_t *));
    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix->data[i] = calloc(cols, sizeof(int32_t));
        if (matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

inline struct float_matrix *create_float_matrix(const size_t rows, const size_t cols)
{
    struct float_matrix *matrix = malloc(sizeof(struct float_matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->data = calloc(rows, sizeof(float64_t *));
    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix->data[i] = calloc(cols, sizeof(float64_t));
        if (matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

inline int initialization_int_matrix(const struct int_matrix *matrix, const int64_t value)
{
    if (matrix == NULL || matrix->data == NULL || matrix->cols <= 0 || matrix->rows <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = value;
        }
    }
    return 0;
}

inline int initialization_float_matrix(const struct float_matrix *matrix, const float value)
{
    if (matrix == NULL || matrix->data == NULL || matrix->cols <= 0 || matrix->rows <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = value;
        }
    }
    return 0;
}

inline struct int_matrix *add_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct int_matrix *matrix = create_int_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_int_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] += arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}


inline struct int_matrix *sub_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct int_matrix *matrix = create_int_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_int_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] -= arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}

void destroy_array_i_2d(int64_t ***ptr, size_t height);
void destroy_array_f_2d(float64_t ***ptr, size_t height);

int create_array_i_2d_rect(int64_t ***ptr, size_t width, size_t height);
int create_array_i_2d_init_rect(int64_t ***ptr, size_t width, size_t height, int64_t value);
int create_array_i_2d_square(int64_t ***ptr, size_t size);
int create_array_i_2d_init_square(int64_t ***ptr, size_t size, int64_t value);

int create_array_f_2d_rect(float64_t ***ptr, size_t width, size_t height);
int create_array_f_2d_init_rect(float64_t ***ptr, size_t width, size_t height, float64_t value);
int create_array_f_2d_square(float64_t ***ptr, size_t size);
int create_array_f_2d_init_square(float64_t ***ptr, size_t size, float64_t value);

void display_array_i_2d(int64_t **ptr, size_t width, size_t height);
void display_array_f_2d(float64_t **ptr, size_t width, size_t height);

int64_t sum_array_i_2d_square(const int64_t **ptr, size_t size);
int64_t sum_array_i_2d_rect(const int64_t **ptr, size_t width, size_t height);

float64_t sum_array_f_2d_square(const float64_t **ptr, size_t size);
float64_t sum_array_f_2d_rect(const float64_t **ptr, size_t width, size_t height);

void add_to_matrix_i_2d_i_square(int64_t **ptr, size_t size, int64_t value);
void add_to_matrix_i_2d_i_rect(int64_t **ptr, size_t width, size_t height, int64_t value);
void add_to_matrix_i_2d_f_square(int64_t **ptr, size_t size, float64_t value);
void add_to_matrix_i_2d_f_rect(int64_t **ptr, size_t width, size_t height, float64_t value);
void add_to_matrix_f_2d_i_square(float64_t **ptr, size_t size, int64_t value);
void add_to_matrix_f_2d_i_rect(float64_t **ptr, size_t width, size_t height, int64_t value);
void add_to_matrix_f_2d_f_square(float64_t **ptr, size_t size, float64_t value);
void add_to_matrix_f_2d_f_rect(float64_t **ptr, size_t width, size_t height, float64_t value);

void mul_to_matrix_i_2d_i_square(int64_t **ptr, size_t size, int64_t value);
void mul_to_matrix_i_2d_i_rect(int64_t **ptr, size_t width, size_t height, int64_t value);
void mul_to_matrix_i_2d_f_square(int64_t **ptr, size_t size, float64_t value);
void mul_to_matrix_i_2d_f_rect(int64_t **ptr, size_t width, size_t height, float64_t value);
void mul_to_matrix_f_2d_i_square(float64_t **ptr, size_t size, int64_t value);
void mul_to_matrix_f_2d_i_rect(float64_t **ptr, size_t width, size_t height, int64_t value);
void mul_to_matrix_f_2d_f_square(float64_t **ptr, size_t size, float64_t value);
void mul_to_matrix_f_2d_f_rect(float64_t **ptr, size_t width, size_t height, float64_t value);

void sub_to_matrix_i_2d_i_square(int64_t **ptr, size_t size, int64_t value);
void sub_to_matrix_i_2d_i_rect(int64_t **ptr, size_t width, size_t height, int64_t value);
void sub_to_matrix_i_2d_f_square(int64_t **ptr, size_t size, float64_t value);
void sub_to_matrix_i_2d_f_rect(int64_t **ptr, size_t width, size_t height, float64_t value);
void sub_to_matrix_f_2d_i_square(float64_t **ptr, size_t size, int64_t value);
void sub_to_matrix_f_2d_i_rect(float64_t **ptr, size_t width, size_t height, int64_t value);
void sub_to_matrix_f_2d_f_square(float64_t **ptr, size_t size, float64_t value);
void sub_to_matrix_f_2d_f_rect(float64_t **ptr, size_t width, size_t height, float64_t value);

void div_to_matrix_i_2d_i_square(int64_t **ptr, size_t size, int64_t value);
void div_to_matrix_i_2d_i_rect(int64_t **ptr, size_t width, size_t height, int64_t value);
void div_to_matrix_i_2d_f_square(int64_t **ptr, size_t size, float64_t value);
void div_to_matrix_i_2d_f_rect(int64_t **ptr, size_t width, size_t height, float64_t value);
void div_to_matrix_f_2d_i_square(float64_t **ptr, size_t size, int64_t value);
void div_to_matrix_f_2d_i_rect(float64_t **ptr, size_t width, size_t height, int64_t value);
void div_to_matrix_f_2d_f_square(float64_t **ptr, size_t size, float64_t value);
void div_to_matrix_f_2d_f_rect(float64_t **ptr, size_t width, size_t height, float64_t value);