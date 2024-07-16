#include "my_matrix.h"

int my_create_matrix(int rows, int columns, matrix_t *result) {
  int exit = OK;
  if (my_size_error(rows, columns) || my_null_matrix(result)) {
    exit = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return exit;
}