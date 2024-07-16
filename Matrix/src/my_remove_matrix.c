#include "my_matrix.h"

void my_remove_matrix(matrix_t *A) {
  if (!my_null_matrix(A) && !my_size_error(A->rows, A->columns)) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
  A->columns = 0;
  A->rows = 0;
}