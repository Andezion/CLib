#include "matrix/matrix.h"

int main(void)
{
    printf("===== Matrix Int =====\n");
    struct int_matrix *matrix_int = create_int_matrix(5, 5);
    display_int_matrix(matrix_int);
    free_int_matrix(&matrix_int);

    printf("\n\n\n");

    printf("===== Matrix Float =====\n");
    struct float_matrix *matrix_float = create_float_matrix(5, 5);
    display_float_matrix(matrix_float);
    free_float_matrix(&matrix_float);

    return 0;
}