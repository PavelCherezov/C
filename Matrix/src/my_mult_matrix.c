#include "my_matrix.h"

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit = OK;
  if (my_null_matrix(A) || my_null_matrix(B) || my_null_matrix(result) ||
      my_size_error(A->rows, A->columns) ||
      my_size_error(B->rows, B->columns)) {
    exit = INCORRECT_MATRIX;
  } else if (B->rows != A->columns || my_regional(A) || my_regional(B)) {
    exit = CALCULATION_ERROR;
  } else {
    my_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] && B->matrix[k][j]
                                      ? A->matrix[i][k] * B->matrix[k][j]
                                      : 0;
        }
      }
    }
  }
  return exit;
}