#include "my_matrix.h"

int my_calc_complements(matrix_t *A, matrix_t *result) {
  int exit = OK;
  if (my_null_matrix(A) || my_size_error(A->rows, A->columns)) {
    exit = INCORRECT_MATRIX;
  } else if (my_regional(A) || A->columns != A->rows || my_null_line(A)) {
    exit = CALCULATION_ERROR;
  } else {
    double determinant = 0.;
    matrix_t invers_A;
    matrix_t invers_trans_A;
    my_inverse_matrix(A, &invers_A);

    my_determinant(A, &determinant);

    my_transpose(&invers_A, &invers_trans_A);

    my_mult_number(&invers_trans_A, determinant, result);

    my_remove_matrix(&invers_A);
    my_remove_matrix(&invers_trans_A);
  }
  return exit;
}