#include "my_matrix.h"

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  int exit = OK;
  if (my_null_matrix(A) || my_null_matrix(result) ||
      my_size_error(A->rows, A->columns)) {
    exit = INCORRECT_MATRIX;
  } else if (my_regional(A) || isinf(number) || isnan(number)) {
    exit = CALCULATION_ERROR;
  } else {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] ? A->matrix[i][j] * number : 0;
      }
    }
  }
  return exit;
}