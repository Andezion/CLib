#include "matrix.h"

int main()
{
    printf("===== Matrix Int =====\n");
    struct int_matrix *matrix_int = create_int_matrix(5, 5);
    display_int_matrix(matrix_int);

    printf("\n");

    printf("===== Initialized Matrix Int =====\n");
    initialization_int_matrix(matrix_int, 5);
    display_int_matrix(matrix_int);
    free_int_matrix(&matrix_int);

    printf("\n");

    printf("===== Error Matrix Int =====\n");
    struct int_matrix *error_numbers_matrix_int = create_int_matrix(-1, -3);
    display_int_matrix(error_numbers_matrix_int);
    free_int_matrix(&error_numbers_matrix_int);

    printf("\n");

    printf("===== Initialized Error Matrix Int =====\n");
    initialization_int_matrix(error_numbers_matrix_int, 5);
    display_int_matrix(error_numbers_matrix_int);
    free_int_matrix(&error_numbers_matrix_int);

    printf("\n\n\n");

    printf("===== Matrix Float =====\n");
    struct float_matrix *matrix_float = create_float_matrix(5, 5);
    display_float_matrix(matrix_float);

    printf("\n");

    printf("===== Initialized Matrix Float =====\n");
    initialization_float_matrix(matrix_float, 4.7);
    display_float_matrix(matrix_float);
    free_float_matrix(&matrix_float);

    printf("\n");

    printf("===== Error Matrix Float =====\n");
    struct float_matrix *error_numbers_matrix_float = create_float_matrix(-1, -3);
    display_float_matrix(error_numbers_matrix_float);
    free_float_matrix(&error_numbers_matrix_float);

    printf("\n");

    printf("===== Initialized Error Matrix Float =====\n");
    initialization_float_matrix(error_numbers_matrix_float, 4.7);
    display_float_matrix(error_numbers_matrix_float);
    free_float_matrix(&error_numbers_matrix_float);

    return 0;
}