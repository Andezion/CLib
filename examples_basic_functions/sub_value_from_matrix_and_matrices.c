#include "matrix_math.h"
#include "matrix.h"

int main()
{
    srand(time(NULL));
    const int64_t value_to_add_int = 5;

    printf("===== Matrix Float One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Random Initialized Matrix Float One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Sub Value from Matrix Float =====\n");
    struct int_matrix *result_int_matrix = sub_value_int_matrices(1, 5, 5, value_to_add_int, matrix_int_one);
    display_int_matrix(result_int_matrix);

    printf("\n");

    printf("===== Matrix Float Two =====\n");
    struct int_matrix *matrix_int_two = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Random Initialized Matrix Float Two =====\n");
    initialization_random_int_matrix(matrix_int_two, 0, 9);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Sub Value from Matrices Float =====\n");
    struct int_matrix *result_int_matrices = sub_value_int_matrices(2, 5, 5, value_to_add_int, matrix_int_one, matrix_int_two);
    display_int_matrix(result_int_matrices);

    printf("\n");

    free_int_matrix(&matrix_int_one);
    free_int_matrix(&matrix_int_two);
    free_int_matrix(&result_int_matrix);
    free_int_matrix(&result_int_matrices);

    printf("\n\n\n");

    const float64_t value_to_add_float = 5.0;

    printf("===== Matrix Float One =====\n");
    struct float_matrix *matrix_float_one = create_float_matrix(5, 5);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Random Initialized Matrix Float One =====\n");
    initialization_random_float_matrix(matrix_float_one, 0, 9);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Sub Value from Matrix Float =====\n");
    struct float_matrix *result_float_matrix = sub_value_float_matrices(1, 5, 5, value_to_add_float, matrix_float_one);
    display_float_matrix(result_float_matrix);

    printf("\n");

    printf("===== Matrix Float Two =====\n");
    struct float_matrix *matrix_float_two = create_float_matrix(5, 5);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Random Initialized Matrix Float Two =====\n");
    initialization_random_float_matrix(matrix_float_two, 0, 9);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Sub Value from Matrices Float =====\n");
    struct float_matrix *result_float_matrices = sub_value_float_matrices(2, 5, 5, value_to_add_float, matrix_float_one, matrix_float_two);
    display_float_matrix(result_float_matrices);

    free_float_matrix(&matrix_float_one);
    free_float_matrix(&matrix_float_two);
    free_float_matrix(&result_float_matrix);
    free_float_matrix(&result_float_matrices);

    return 0;
}