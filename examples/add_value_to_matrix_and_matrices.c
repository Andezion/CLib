#include "matrix_math.h"
#include "matrix.h"

int main()
{
    srand(time(NULL));

    printf("===== Matrix Int One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Random Initialized Matrix Int One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n");

    const int64_t value_to_add = 5;

    printf("===== Add Value to Matrix Int One =====\n");
    struct int_matrix *result_int_matrix = add_value_int_matrices(1, 5, 5, value_to_add, matrix_int_one);
    display_int_matrix(result_int_matrix);

    printf("\n");

    free_int_matrix(&matrix_int_one);
    free_int_matrix(&result_int_matrix);

    return 0;
}