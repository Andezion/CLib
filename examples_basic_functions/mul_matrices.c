#include "matrix_math.h"
#include "matrix.h"

int main()
{
    srand(time(NULL));

    printf("===== Matrix Int One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(3, 3);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Random Initialized Matrix Int One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n");

    printf("===== Matrix Int Two =====\n");
    struct int_matrix *matrix_int_two = create_int_matrix(3, 3);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Random Initialized Matrix Int Two =====\n");
    initialization_random_int_matrix(matrix_int_two, 0, 9);
    display_int_matrix(matrix_int_two);

    printf("\n");

    printf("===== Result Matrix Int =====\n");

    struct int_matrix *matrix_result_int = mul_int_matrices(2, matrix_int_one, matrix_int_two);
    display_int_matrix(matrix_result_int);

    free_int_matrix(&matrix_result_int);
    free_int_matrix(&matrix_int_one);
    free_int_matrix(&matrix_int_two);

    printf("\n\n\n");

    printf("===== Matrix Float One =====\n");
    struct float_matrix *matrix_float_one = create_float_matrix(3, 3);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Random Initialized Matrix Float One =====\n");
    initialization_random_float_matrix(matrix_float_one, 0.0, 9.0);
    display_float_matrix(matrix_float_one);

    printf("\n");

    printf("===== Matrix Float Two =====\n");
    struct float_matrix *matrix_float_two = create_float_matrix(3, 3);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Random Initialized Matrix Float Two =====\n");
    initialization_random_float_matrix(matrix_float_two, 0.0, 9.0);
    display_float_matrix(matrix_float_two);

    printf("\n");

    printf("===== Result Matrix Float =====\n");

    struct float_matrix *matrix_result_float = mul_float_matrices(2, matrix_float_one, matrix_float_two);
    display_float_matrix(matrix_result_float);

    free_float_matrix(&matrix_result_float);
    free_float_matrix(&matrix_float_one);
    free_float_matrix(&matrix_float_two);

    return 0;
}