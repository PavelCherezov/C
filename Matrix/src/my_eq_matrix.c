#include "my_matrix.h"

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int exit = SUCCESS;
  if (my_null_matrix(A) || my_null_matrix(B) || my_chec_size(A, B) ||
      my_regional(A) || my_regional(B)) {
    exit = FAILURE;
  } else {
    for (int i = 0; i < A->rows && exit; i++) {
      for (int j = 0; j < A->columns && exit; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
          exit = FAILURE;
        }
      }
    }
  }
  return exit;
}