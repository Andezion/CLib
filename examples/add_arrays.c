#include "array_math.h"

int main(void)
{
    srand(time(NULL));

    printf("===== Array Int One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Random Initialized Array Int One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Array Int Two =====\n");
    struct int_matrix *matrix_int_two = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Random Initialized Array Int Two =====\n");
    initialization_random_int_matrix(matrix_int_two, 0, 9);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Result Array Int =====\n");

    struct int_matrix *matrix_result_int = add_int_matrices(2, 5, 5, matrix_int_one, matrix_int_two);
    display_int_matrix(matrix_result_int);

    free_int_matrix(&matrix_result_int);
    free_int_matrix(&matrix_int_two);
    free_int_matrix(&matrix_int_one);

    printf("\n");

    printf("===== Error Array Int One =====\n");
    struct int_matrix *error_numbers_matrix_int_one = create_int_matrix(-1, -3);
    display_int_matrix(error_numbers_matrix_int_one);

    printf("\n");

    printf("===== Initialized Error Array Int One =====\n");
    initialization_int_matrix(error_numbers_matrix_int_one, 5);
    display_int_matrix(error_numbers_matrix_int_one);

    printf("\n");

    printf("===== Error Array Int Two =====\n");
    struct int_matrix *error_numbers_matrix_int_two = create_int_matrix(-1, -3);
    display_int_matrix(error_numbers_matrix_int_two);

    printf("\n");

    printf("===== Initialized Error Array Int Two =====\n");
    initialization_int_matrix(error_numbers_matrix_int_two, 5);
    display_int_matrix(error_numbers_matrix_int_two);

    printf("\n");

    printf("===== Result Array Int =====\n");

    struct int_matrix *matrix_result_int_error = add_int_matrices(2, 5, 5, error_numbers_matrix_int_one, error_numbers_matrix_int_two);
    display_int_matrix(matrix_result_int_error);

    free_int_matrix(&error_numbers_matrix_int_one);
    free_int_matrix(&error_numbers_matrix_int_two);

    printf("\n\n\n");

    printf("===== Array Float One =====\n");
    struct float_matrix *matrix_float_one = create_float_matrix(5, 5);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Random Initialized Array Float One =====\n");
    initialization_random_float_matrix(matrix_float_one, 0.0, 9.0);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Array Float Two =====\n");
    struct float_matrix *matrix_float_two = create_float_matrix(5, 5);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Random Initialized Array Float Two =====\n");
    initialization_random_float_matrix(matrix_float_two, 0.0, 9.0);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Result Array Float =====\n");

    struct float_matrix *matrix_result_float = add_float_matrices(2, 5, 5, matrix_float_one, matrix_float_two);
    display_float_matrix(matrix_result_float);

    free_float_matrix(&matrix_result_float);
    free_float_matrix(&matrix_float_one);
    free_float_matrix(&matrix_float_two);

    return 0;
}