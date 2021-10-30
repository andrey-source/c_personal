#include "naive_transpose.h"
#include <string.h>


bool naive_transpose(double * matrix, size_t *n_rows, size_t *n_columns)
{
    size_t size = *n_rows * *n_columns;
    if (size <= 1 || !matrix)
            return false;

    double *copy_matrix = (double*)malloc(size * sizeof(double));
    memcpy(copy_matrix, matrix, size * sizeof(double));
    
    for (size_t idx = 0; idx < size; idx++)
    {
        size_t i = idx / *n_columns;
        size_t j = idx % *n_columns;
        matrix[j * *n_rows + i] = copy_matrix[idx];
    }
    free(copy_matrix);
    size_t temp = *n_rows;
    *n_rows = *n_columns;
    *n_columns = temp;
    return true;
}
