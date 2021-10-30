#include "gtest/gtest.h"
#include <stdio.h>
#include <fstream>
#include <string.h>




extern "C"
{
    #include "naive_transpose.h"
}


TEST (NAIVE_TRANSPOSE, INCORRECT_SIZE)
{
    size_t n_rows = 1;
    size_t n_columns = 1;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size *sizeof(double));
    for (size_t i = 0; i < size; i++)
        matrix[i] = i * 1.1;
    EXPECT_EQ(naive_transpose(matrix, &n_rows, &n_columns), false);
    free(matrix);
}

TEST (NAIVE_TRANSPOSE, EMPTY_DATA)
{
    size_t n_rows = 1;
    size_t n_columns = 2;
    EXPECT_EQ(naive_transpose(NULL, &n_rows, &n_columns), false);
}


TEST (NAIVE_TRANSPOSE, FUNCTIONAL)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size * sizeof(double));
    double *copy_matrix = (double*)malloc(size * sizeof(double));
    for (size_t i = 0; i < size; i++)
        matrix[i] = i * 1.1;
    memcpy(copy_matrix, matrix, size * sizeof(double));
    ASSERT_EQ(naive_transpose(matrix, &n_rows, &n_columns), true);
    for (size_t i = 0; i < n_rows; i++)
        for (size_t j = 0; j < n_columns; j++)
            EXPECT_DOUBLE_EQ(matrix[n_columns * i + j], copy_matrix[n_rows * j + i]);
    free(matrix);
    free(copy_matrix);
}

TEST (NAIVE_TRASPOSE, CHECK_RESIZE)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    size_t size = n_rows * n_columns;
    double *matrix = (double*)malloc(size * sizeof(double));
    for (size_t i = 0; i < size; i++)
        matrix[i] = i * 1.1;
    ASSERT_EQ(naive_transpose(matrix, &n_rows, &n_columns), true);
    EXPECT_EQ(n_rows, 2);
    EXPECT_EQ(n_columns, 3);
    free(matrix);

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
