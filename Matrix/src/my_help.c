#include "my_matrix.h"

// Проверка строк и столбцов на <= 0 (0 - всё хорошо, 1 - ошибка)
int my_size_error(int rows, int columns) { return rows <= 0 || columns <= 0; }

// Проверка указателя на NULL (0 - всё хорошо, 1 - ошибка)
int my_null_matrix(matrix_t *matrix) { return matrix == NULL; }

// Проверка на равенство размеров матрицы (0 - всё хорошо, 1 - размер матриц не
// равен)
int my_chec_size(matrix_t *A, matrix_t *B) {
  return A->columns != B->columns || A->rows != B->rows;
}

// Проверка значений матрици на бесконечность и NAN (0 - всё хорошо, 1 -
// значение не корректное)
int my_regional(matrix_t *A) {
  int exit = 0;
  for (int i = 0; i < A->rows && !exit; i++) {
    for (int j = 0; j < A->columns && !exit; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        exit = 1;
      }
    }
  }
  return exit;
}

// Проверка на нулевою строку или столбик (0 - всё хорошо, 1 - есть 0 строка или
// столбец)
int my_null_line(matrix_t *A) {
  int exit = 0;
  double summ_column, summ_row;
  for (int i = 0; i < A->rows; i++) {
    summ_column = 0;
    summ_row = 0;
    for (int j = 0; j < A->columns; j++) {
      summ_column += fabs(A->matrix[j][i]);
      summ_row += fabs(A->matrix[i][j]);
    }
    if (summ_column == 0 || summ_row == 0) {
      exit = 1;
      break;
    }
  }
  return exit;
}

// Копирует матрицу А в матрицу В
void my_copy_matrix(matrix_t *A, matrix_t *B) {
  my_create_matrix(A->rows, A->columns, B);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

// Копирует матрицу А в матрицу В и добавляет единичную справа
void my_unit_matrix(matrix_t *A, matrix_t *B) {
  my_create_matrix(A->rows, A->columns * 2, B);
  for (int i = 0; i < B->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      if (j < A->columns) {
        B->matrix[i][j] = A->matrix[i][j];
      } else if (j % A->rows == i && j >= A->columns) {
        B->matrix[i][j] = 1.;
      } else {
        B->matrix[i][j] = 0.;
      }
    }
  }
}

// Создание угловой матрици обнуляя все ниже главной диагонали
void my_frimen(matrix_t *A, int *znak) {
  double *buff = NULL;
  double multiple = 0.;
  for (int i = 0; i < A->rows; i++) {
    if (!A->matrix[i][i]) {
      for (int j = i; j < A->columns; j++) {
        if (A->matrix[j][i]) {
          buff = A->matrix[j];
          A->matrix[j] = A->matrix[i];
          A->matrix[i] = buff;
          *znak *= -1;
          break;
        }
      }
    }
    if (i < A->columns - 1) {
      for (int n = i; n < A->rows - 1; n++) {
        multiple = A->matrix[n + 1][i] / A->matrix[i][i];
        for (int m = i; m < A->columns; m++) {
          A->matrix[n + 1][m] -= A->matrix[i][m] * multiple;
        }
      }
    }
  }
}

// Создание угловой матрици обнуляя все выше главной диагонали
void my_frimen_invers(matrix_t *A) {
  double multiple = 0.;
  for (int i = A->rows - 1; i >= 0; i--) {
    for (int n = i; n > 0; n--) {
      multiple = A->matrix[n - 1][i] / A->matrix[i][i];
      for (int m = A->columns - 1; m >= 0; m--) {
        A->matrix[n - 1][m] -= A->matrix[i][m] * multiple;
      }
    }
  }
}

void my_fill_matrix(matrix_t *A, char *src) {
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      sscanf(src, "%lf ", &(A->matrix[row][column]));
      src += strcspn(src, " ") + 1;
    }
  }
}