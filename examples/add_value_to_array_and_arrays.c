#include "array_math.h"
#include "array.h"

int main()
{
    srand(time(NULL));
    const int64_t value_to_add_int = 5;

    printf("===== Array Int One =====\n");
    struct int_array *array_int_one = create_int_array(5);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Random Initialized Array Int One =====\n");
    initialization_random_int_array(array_int_one, 0, 9);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Add Value to Array Int =====\n");
    struct int_array *result_int_array = add_value_to_int_arrays(1, 5, value_to_add_int, array_int_one);
    display_int_array(result_int_array);

    printf("\n");

    printf("===== Array Int Two =====\n");
    struct int_array *array_int_two = create_int_array(5);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Random Initialized Array Int Two =====\n");
    initialization_random_int_array(array_int_two, 0, 9);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Add Value to Arrays =====\n");
    struct int_array *result_int_arrays = add_value_to_int_arrays(2, 5, 5, value_to_add_int, array_int_one, array_int_two);
    display_int_array(result_int_arrays);

    printf("\n");

    free_int_array(&array_int_one);
    free_int_array(&array_int_two);
    free_int_array(&result_int_array);
    free_int_array(&result_int_arrays);

    printf("\n\n\n");

    const float64_t value_to_add_float = 5.0;

    printf("===== Array Float One =====\n");
    struct float_array *array_float_one = create_float_array(5);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Random Initialized Array Float One =====\n");
    initialization_random_float_array(array_float_one, 0, 9);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Add Value to Array Float =====\n");
    struct float_array *result_float_array = add_value_float_array(1, 5, value_to_add_float, array_float_one);
    display_float_array(result_float_array);

    printf("\n");

    printf("===== Array Float Two =====\n");
    struct float_matrix *matrix_float_two = create_float_matrix(5, 5);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Random Initialized Array Float Two =====\n");
    initialization_random_float_matrix(matrix_float_two, 0, 9);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Add Value to Arrays Float =====\n");
    struct float_matrix *result_float_matrices = add_value_float_matrices(2, 5, 5, value_to_add_float, matrix_float_one, matrix_float_two);
    display_float_matrix(result_float_matrices);

    free_float_matrix(&matrix_float_one);
    free_float_matrix(&matrix_float_two);
    free_float_matrix(&result_float_matrix);
    free_float_matrix(&result_float_matrices);

    return 0;
}