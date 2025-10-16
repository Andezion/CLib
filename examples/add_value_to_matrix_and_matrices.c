#include "matrix_math.h"
#include "matrix.h"

int main()
{
    srand(time(NULL));
    const int64_t value_to_add = 5;


    printf("===== Matrix Int One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Random Initialized Matrix Int One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Add Value to Matrix Int =====\n");
    struct int_matrix *result_int_matrix = add_value_int_matrices(1, 5, 5, value_to_add, matrix_int_one);
    display_int_matrix(result_int_matrix);

    printf("\n");

    printf("===== Matrix Int Two =====\n");
    struct int_matrix *matrix_int_two = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Random Initialized Matrix Int Two =====\n");
    initialization_random_int_matrix(matrix_int_two, 0, 9);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Add Value to Matrices =====\n");
    struct int_matrix *result_int_matrices = add_value_int_matrices(2, 5, 5, value_to_add, matrix_int_one, matrix_int_two);
    display_int_matrix(result_int_matrices);

    printf("\n");

    free_int_matrix(&matrix_int_one);
    free_int_matrix(&matrix_int_two);
    free_int_matrix(&result_int_matrix);
    free_int_matrix(&result_int_matrices);

    return 0;
}