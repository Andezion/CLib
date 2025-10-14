#include "matrix_math.h"
#include "matrix.h"

int main()
{
    srand(time(NULL));

    printf("===== Matrix Int One =====\n");
    struct int_matrix *matrix_int_one = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_one);

    printf("\n\n\n");

    printf("===== Random Initialized Matrix Int One =====\n");
    initialization_random_int_matrix(matrix_int_one, 0, 9);
    display_int_matrix(matrix_int_one);

    printf("\n\n\n");

    printf("===== Matrix Int Two =====\n");
    struct int_matrix *matrix_int_two = create_int_matrix(5, 5);
    display_int_matrix(matrix_int_two);

    printf("\n\n\n");

    printf("===== Random Initialized Matrix Int Two =====\n");
    initialization_random_int_matrix(matrix_int_two, 0, 9);
    display_int_matrix(matrix_int_two);

    printf("\n\n\n");

    printf("===== Result Matrix Int =====\n");

    const struct int_matrix *matrix_result = add_int_matrices(2, 5, 5, matrix_int_one, matrix_int_two);
    display_int_matrix(matrix_result);

    printf("\n\n\n");

    return 0;
}