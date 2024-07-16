#ifndef MY_MATRIX_h
#define MY_MATRIX_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum result_code { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Вспомогательные функции

int my_size_error(int rows, int columns);
int my_null_matrix(matrix_t *matrix);
int my_chec_size(matrix_t *A, matrix_t *B);
int my_regional(matrix_t *A);
int my_null_line(matrix_t *A);
void my_copy_matrix(matrix_t *A, matrix_t *B);
void my_unit_matrix(matrix_t *A, matrix_t *B);
void my_frimen(matrix_t *A, int *znak);
void my_frimen_invers(matrix_t *A);
void my_fill_matrix(matrix_t *A, char *src);

// Основные функции

int my_create_matrix(int rows, int columns, matrix_t *result);
void my_remove_matrix(matrix_t *A);
int my_eq_matrix(matrix_t *A, matrix_t *B);
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_mult_number(matrix_t *A, double number, matrix_t *result);
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_transpose(matrix_t *A, matrix_t *result);
int my_calc_complements(matrix_t *A, matrix_t *result);
int my_determinant(matrix_t *A, double *result);
int my_inverse_matrix(matrix_t *A, matrix_t *result);

#endif