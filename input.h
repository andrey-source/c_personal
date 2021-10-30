#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 10000



bool input_size(size_t * n_rows, size_t * n_columns, FILE * stream);
bool fill_matrix(double *matrix, const size_t n_rows, const size_t n_columns, FILE *stream);
bool input(double **matrix, size_t *n_rows, size_t *n_columns, FILE *stream);
