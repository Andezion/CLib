#include "matrix_math.h"
#include "matrix.h"

int main()
{
    printf("===== Matrix Int =====\n");
    struct int_matrix *matrix_int = create_int_matrix(5, 5);
    display_int_matrix(matrix_int);

    printf("\n");

    printf("===== Sum Matrix Int =====\n");
    int64_t sum = sum_int_matrix(matrix_int);
    printf("Sum is = %lld\n", sum);

    printf("\n\n\n");

    printf("===== Initialized Matrix Int =====\n");
    initialization_int_matrix(matrix_int, 5);
    display_int_matrix(matrix_int);

    printf("\n");

    printf("===== Sum Matrix Int =====\n");
    sum = sum_int_matrix(matrix_int);
    printf("Sum is = %lld\n", sum);
    free_int_matrix(&matrix_int);

    printf("\n\n\n");

    printf("===== Matrix Float =====\n");
    struct float_matrix *matrix_float = create_float_matrix(5, 5);
    display_float_matrix(matrix_float);

    printf("\n");

    printf("===== Sum Matrix Float =====\n");
    float64_t sum_float = sum_float_matrix(matrix_float);
    printf("Sum is = %f\n", sum_float);

    printf("\n\n\n");

    printf("===== Initialized Matrix Float =====\n");
    initialization_float_matrix(matrix_float, 6.2);
    display_float_matrix(matrix_float);

    printf("\n");

    printf("===== Sum Matrix Float =====\n");
    sum_float = sum_float_matrix(matrix_float);
    printf("Sum is = %f\n", sum_float);
    free_float_matrix(&matrix_float);

    return 0;
}