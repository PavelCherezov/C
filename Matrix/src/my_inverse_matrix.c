#include "my_matrix.h"

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  int exit = OK;
  double det = 1.;
  my_determinant(A, &det);
  if (my_null_matrix(A) || my_size_error(A->rows, A->columns)) {
    exit = INCORRECT_MATRIX;
  } else if (my_regional(A) || A->columns != A->rows || my_null_line(A) ||
             det == 0) {
    exit = CALCULATION_ERROR;
  } else {
    my_create_matrix(A->rows, A->columns, result);
    int znak = 1;
    matrix_t copy_A;
    double multiple = 0.;
    my_unit_matrix(A, &copy_A);
    my_frimen(&copy_A, &znak);
    my_frimen_invers(&copy_A);
    for (int i = 0; i < copy_A.rows; i++) {
      multiple = 1 / copy_A.matrix[i][i];
      for (int j = 0; j < copy_A.columns; j++) {
        copy_A.matrix[i][j] =
            copy_A.matrix[i][j] != 0 ? copy_A.matrix[i][j] * multiple : 0;
      }
    }

    for (int i = 0; i < copy_A.rows; i++) {
      for (int j = result->columns; j < copy_A.columns; j++) {
        result->matrix[i][j - result->columns] = copy_A.matrix[i][j];
      }
    }
    my_remove_matrix(&copy_A);
  }
  return exit;
}