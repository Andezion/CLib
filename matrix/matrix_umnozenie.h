#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_UMNOZENIE_H
#define MATRIX_UMNOZENIE_H

typedef struct {
    size_t rows;
    size_t cols;
    double *data;
}Matrix;

Matrix createMatrix(size_t rows, size_t cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = calloc(rows * cols, sizeof(double));
    if (m.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(m.data);
        exit(1);
    }
    return m;
}
void freeMatrix(Matrix *m) {
    free(m->data);
    m->data = NULL;
    m->rows = m->cols = 0;
}

double get(const Matrix *m, size_t i, size_t j) {
    return m->data[i * m->cols + j] ;
}
void set(Matrix *m, size_t i, size_t j, double val) {
    m->data[i * m->cols + j] = val;
}
Matrix multiplyMatrix(Matrix *a, Matrix *b) {
    if (a->cols != b->rows) {
        fprintf(stderr, "Matrix multiplication error\n", a->rows, a->cols,b->cols,b->rows);
        freeMatrix(a);
        exit(1);
    }

    Matrix result = createMatrix(a -> rows, b -> cols);
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < a->cols; k++) {
                sum += get(a, i, k) * get(b, k, j);
            }
            set(&result, i, j, sum);
        }
    }
    return result;
}
void printMatrix(Matrix *m) {
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            printf("%.2f ", get(m, i, j));
        }
        printf("\n");
    }
}
#endif //MATRIX_UMNOZENIE_H
