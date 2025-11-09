#include "array.h"

int main(void)
{
    printf("===== Array Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);
    destroy_int_array(&array_int);

    printf("\n");

    // printf("===== Error Array Int =====\n");
    // struct int_array *error_numbers_matrix_int = create_int_matrix(-1, -3);
    // display_int_matrix(error_numbers_matrix_int);
    // free_int_matrix(&error_numbers_matrix_int);
    //
    // printf("\n\n\n");
    //
    // printf("===== Array Float =====\n");
    // struct float_array *matrix_float = create_float_matrix(5, 5);
    // display_float_matrix(matrix_float);
    // free_float_matrix(&matrix_float);
    //
    // printf("\n");
    //
    // printf("===== Error Array Float =====\n");
    // struct float_array *error_numbers_matrix_float = create_float_matrix(-1, -3);
    // display_float_matrix(error_numbers_matrix_float);
    // free_float_matrix(&error_numbers_matrix_float);
}