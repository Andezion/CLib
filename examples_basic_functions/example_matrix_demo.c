#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../matrix/matrix_math.h"

int main(void)
{
    struct float_matrix *A = create_float_matrix(3, 3);
    struct float_matrix *B = create_float_matrix(3, 3);

    if (!A || !B)
    {
        return 1;
    }

    const float64_t avals[3][3] = {{4, 2, 1},{0, 1, 5},{2, 3, 3}};
    const float64_t bvals[3][3] = {{1, 0, 2},{-1, 3, 1},{0, 2, 4}};

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            A->data[i][j] = avals[i][j]; B->data[i][j] = bvals[i][j];
        }
    }

    printf("Matrix A:\n");
    display_float_matrix(A);

    printf("Matrix B:\n");
    display_float_matrix(B);

    struct float_matrix *C = mul_float_matrices(2, A, B);

    printf("A * B =\n");
    display_float_matrix(C);

    struct float_matrix *I = create_float_matrix(3, 3);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            I->data[i][j] = i == j ? 1.0 : 0.0;
        }
    }


    struct float_matrix *invA = div_float_matrices(2, I, A);
    if (invA)
    {
        printf("inv(A) =\n"); display_float_matrix(invA);

        struct float_matrix *bmat = create_float_matrix(3,1);
        bmat->data[0][0] = 1; bmat->data[1][0] = 2; bmat->data[2][0] = 3;

        struct float_matrix *x = mul_float_matrices(2, invA, bmat);
        printf("Solution x (inv(A)*b) =\n"); display_float_matrix(x);

        free_float_matrix(&bmat);
        free_float_matrix(&x);
    }

    free_float_matrix(&A); free_float_matrix(&B); free_float_matrix(&C); free_float_matrix(&I); free_float_matrix(&invA);

    return 0;
}
