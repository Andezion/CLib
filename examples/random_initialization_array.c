#include "array.h"

int main()
{
    srand(time(NULL));

    printf("===== Matrix Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);

    printf("\n");

    printf("===== Random Initialized Matrix Int =====\n");
    initialization_random_int_array(array_int, 0, 99);
    display_int_array(array_int);
    free_int_array(&array_int);

    printf("\n");

    printf("===== Error Matrix Int =====\n");
    struct int_array *error_numbers_array_int = create_int_array(-4);
    display_int_array(error_numbers_array_int);
    free_int_array(&error_numbers_array_int);

    printf("\n");

    printf("===== Initialized Error Matrix Int =====\n");
    initialization_random_int_array(array_int, 0, 99);
    display_int_array(error_numbers_array_int);
    free_int_array(&error_numbers_array_int);

    printf("\n\n\n");
    //
    // printf("===== Matrix Float =====\n");
    // struct float_matrix *matrix_float = create_float_matrix(5, 5);
    // display_float_matrix(matrix_float);
    //
    // printf("\n");
    //
    // printf("===== Random Initialized Matrix Float =====\n");
    // initialization_random_float_matrix(matrix_float, 0.0, 99.0);
    // display_float_matrix(matrix_float);
    // free_float_matrix(&matrix_float);
    //
    // printf("\n");
    //
    // printf("===== Error Matrix Float =====\n");
    // struct float_matrix *error_numbers_matrix_float = create_float_matrix(-1, -3);
    // display_float_matrix(error_numbers_matrix_float);
    // free_float_matrix(&error_numbers_matrix_float);
    //
    // printf("\n");
    //
    // printf("===== Initialized Error Matrix Float =====\n");
    // initialization_random_float_matrix(matrix_float, 0.0, 99.0);
    // display_float_matrix(error_numbers_matrix_float);
    // free_float_matrix(&error_numbers_matrix_float);

    return 0;
}