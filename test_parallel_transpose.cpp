#include "gtest/gtest.h"
#include <stdio.h>
#include <fstream>
#include <string.h>




extern "C"
{
    #include "parallel_transpose.c"
}


double matrix_3x2[6] = {1.1, 2.2,
                        3.3, 4.4, 
                        5.5, 6.6};

double matrix_2x3_T[6] = {1.1, 3.3, 5.5,
                          2.2, 4.4, 6.6};


TEST (PARALLEL_TRANSPOSE, INCORRECT_SIZE)
{
    size_t n_rows = 1;
    size_t n_columns = 1;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size *sizeof(double));
    for (size_t i = 0; i < size; i++)
        matrix[i] = i * 1.1;
    EXPECT_EQ(parallel_transpose(matrix, &n_rows, &n_columns), false);
    free(matrix);
}

TEST (PARALLEL_TRANSPOSE, RESIZE)
{
    size_t n_rows = 2;
    size_t n_columns = 1;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size *sizeof(double));
    for (size_t i = 0; i < size; i++)
        matrix[i] = i * 1.1;
    ASSERT_EQ(parallel_transpose(matrix, &n_rows, &n_columns), true);
    EXPECT_EQ(n_rows, 1);
    EXPECT_EQ(n_columns, 2);
    free(matrix);
}



TEST (PARALLEL_TRANSPOSE, EMPTY_DATA)
{
    size_t n_rows = 1;
    size_t n_columns = 2;
    EXPECT_EQ(parallel_transpose(NULL, &n_rows, &n_columns), false);
}


// transpose only second row
TEST (PARALLEL_TRANSPOSE, BUTCH_TRANSPOSE)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size * sizeof(double));
    double *copy_matrix = (double*)malloc(size * sizeof(double));
    for (size_t i = 0; i < size; i++)
    {
        matrix[i] = matrix_3x2[i];
        copy_matrix[i] = matrix_3x2[i];
    }
    args args_butch = fill_args(matrix, copy_matrix, 2, 4, n_rows, n_columns);
    butch_transpose((void*)&args_butch);
    EXPECT_DOUBLE_EQ(matrix[1], matrix_2x3_T[1]);
    EXPECT_DOUBLE_EQ(matrix[4], matrix_2x3_T[4]);

    EXPECT_DOUBLE_EQ(matrix[0], matrix_3x2[0]);
    EXPECT_DOUBLE_EQ(matrix[2], matrix_3x2[2]);
    EXPECT_DOUBLE_EQ(matrix[3], matrix_3x2[3]);
    EXPECT_DOUBLE_EQ(matrix[5], matrix_3x2[5]);
    free(matrix);
    free(copy_matrix);
}


TEST (PARALLEL_TRANSPOSE, FUNCTIONAL)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size * sizeof(double));
    for (size_t i = 0; i < size; i++)
    {
        matrix[i] = matrix_3x2[i];
    }
    ASSERT_EQ(parallel_transpose(matrix, &n_rows, &n_columns), true);
    for (size_t i = 0; i < size; i++)
        EXPECT_DOUBLE_EQ(matrix[i], matrix_2x3_T[i]);
    free(matrix);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
