#include "matrix_math.h"
#include "matrix/matrix.h"

int main()
{
    printf("===== Matrix Int =====\n");
    struct int_matrix *matrix_int = create_int_matrix(5, 5);
    display_int_matrix(matrix_int);

    printf("\n");

    printf("===== Sum Matrix Int =====\n");
    int64_t sum = sum_int_matrix(matrix_int);
    printf("Sum is = %lld\n", sum);

    printf("\n\n\n");

    printf("===== Initialized Matrix Int =====\n");
    initialization_int_matrix(matrix_int, 5);
    display_int_matrix(matrix_int);

    printf("\n");

    printf("===== Sum Matrix Int =====\n");
    sum = sum_int_matrix(matrix_int);
    printf("Sum is = %lld\n", sum);

    free_int_matrix(&matrix_int);
    return 0;
}