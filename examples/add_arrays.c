#include "array_math.h"

int main(void)
{
    srand(time(NULL));

    printf("===== Array Int One =====\n");
    struct int_array *array_int_one = create_int_array(5);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Random Initialized Array Int One =====\n");
    initialization_random_int_array(array_int_one, 0, 9);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Array Int Two =====\n");
    struct int_array *array_int_two = create_int_array(5);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Random Initialized Array Int Two =====\n");
    initialization_random_int_array(array_int_two, 0, 9);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Result Array Int =====\n");

    struct int_array *array_result_int = add_int_arrays(2, 5, array_int_one, array_int_two);
    display_int_array(array_result_int);

    free_int_array(&array_result_int);
    free_int_array(&array_int_one);
    free_int_array(&array_int_two);

    printf("\n");

    printf("===== Error Array Int One =====\n");
    struct int_array *error_numbers_array_int_one = create_int_array(-3);
    display_int_array(error_numbers_array_int_one);

    printf("\n");

    printf("===== Initialized Error Array Int One =====\n");
    initialization_int_array(error_numbers_array_int_one, 5);
    display_int_array(error_numbers_array_int_one);

    printf("\n");

    printf("===== Error Array Int Two =====\n");
    struct int_array *error_numbers_array_int_two = create_int_array(-3);
    display_int_array(error_numbers_array_int_two);

    printf("\n");

    printf("===== Initialized Error Array Int Two =====\n");
    initialization_int_array(error_numbers_array_int_two, 5);
    display_int_array(error_numbers_array_int_two);

    printf("\n");

    printf("===== Result Array Int =====\n");

    struct int_array *array_result_int_error = add_int_arrays(2, 5, error_numbers_array_int_one, error_numbers_array_int_two);
    display_int_array(array_result_int_error);

    free_int_array(&array_result_int_error);
    free_int_array(&error_numbers_array_int_one);
    free_int_array(&error_numbers_array_int_two);

    printf("\n\n\n");
    //
    // printf("===== Array Float One =====\n");
    // struct float_array *matrix_float_one = create_float_matrix(5, 5);
    // display_float_array(matrix_float_one);
    //
    // printf("\n");
    //
    // printf("===== Random Initialized Array Float One =====\n");
    // initialization_random_float_matrix(matrix_float_one, 0.0, 9.0);
    // display_float_array(matrix_float_one);
    //
    // printf("\n");
    //
    // printf("===== Array Float Two =====\n");
    // struct float_array *matrix_float_two = create_float_array(5, 5);
    // display_float_array(matrix_float_two);
    //
    // printf("\n");
    //
    // printf("===== Random Initialized Array Float Two =====\n");
    // initialization_random_float_array(matrix_float_two, 0.0, 9.0);
    // display_float_array(matrix_float_two);
    //
    // printf("\n");
    //
    // printf("===== Result Array Float =====\n");
    //
    // struct float_array *array_result_float = add_float_arrays(2, 5, 5, array_float_one, array_float_two);
    // display_float_array(array_result_float);
    //
    // free_float_array(&array_result_float);
    // free_float_array(&array_float_one);
    // free_float_array(&array_float_two);

    return 0;
}