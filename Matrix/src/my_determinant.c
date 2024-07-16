#include "my_matrix.h"

int my_determinant(matrix_t *A, double *result) {
  int exit = OK;
  if (my_null_matrix(A) || my_size_error(A->rows, A->columns)) {
    exit = INCORRECT_MATRIX;
  } else if (my_regional(A) || A->columns != A->rows) {
    exit = CALCULATION_ERROR;
  } else {
    if (my_null_line(A)) {
      *result = 0.;
    } else {
      int znak = 1;
      *result = 1.;
      matrix_t copy_A;
      my_copy_matrix(A, &copy_A);
      my_frimen(&copy_A, &znak);
      for (int n = 0; n < copy_A.rows; n++) {
        *result *= copy_A.matrix[n][n];
      }
      *result *= znak;
      my_remove_matrix(&copy_A);
    }
  }
  return exit;
}