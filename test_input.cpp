#include <stdio.h>
#include <gtest/gtest.h>
#include <fstream>



extern "C" 
{
    #include "input.h"
}




TEST (INPUT_SIZE, INCORRECT_INPUT_NO_NUM)
{
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "no number";
    test_file.close();
    size_t n_rows = 0;
    size_t n_columns = 0;
    FILE *stream = fopen("test.txt", "r");
    ASSERT_EQ(input_size(&n_rows, &n_columns, stream), false);
    remove("test.txt");
}

TEST (INPUT_SIZE, INCORRECT_INPUT_NO_UNSIGNED)
{
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "-3 1";
    test_file.close();
    size_t n_rows = 0;
    size_t n_columns = 0;
    FILE *stream = fopen("test.txt", "r");
    ASSERT_EQ(input_size(&n_rows, &n_columns, stream), false);
    remove("test.txt");
}


TEST (INPUT_SIZE, CHECK_VALUES)
{
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "3 2";
    test_file.close();
    size_t n_rows = 0;
    size_t n_columns = 0;
    FILE *stream = fopen("test.txt", "r");
    ASSERT_TRUE(input_size(&n_rows, &n_columns, stream));
    EXPECT_EQ(n_rows, 3);
    EXPECT_EQ(n_columns, 2);
    remove("test.txt");
}



TEST (FILL_MATRIX, INCORRECT_DATA)
{
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "3 5 1 number 4 4";
    test_file.close();
    size_t n_rows = 3;
    size_t n_columns = 2;
    double* matrix = (double*)malloc(n_rows * n_columns * sizeof(double));
    FILE *stream = fopen("test.txt", "r");
    ASSERT_EQ(fill_matrix(matrix, n_rows, n_columns, stream), false);
    free(matrix);
    remove("test.txt");
}


TEST (FILL_MATRIX, INCORRECT_TYPE_DATA)
{
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "3 5 1 number 4 4";
    test_file.close();
    size_t n_rows = 3;
    size_t n_columns = 2;
    double* matrix = (double*)malloc(n_rows * n_columns * sizeof(double));
    FILE *stream = fopen("test.txt", "r");
    EXPECT_EQ(fill_matrix(matrix, n_rows, n_columns, stream), false);
    free(matrix);
    remove("test.txt");
}



TEST (FILL_MATRIX, INCORRECT_SIZE_DATA)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    std::ofstream test_file;
    test_file.open("test.txt");

    for (size_t i = 0; i < n_rows * n_columns - 1; i++)
        test_file << i * 1.1 << std::endl;

    test_file.close();
    double* matrix = (double*)malloc(n_rows * n_columns * sizeof(double));
    FILE *stream = fopen("test.txt", "r");
    EXPECT_EQ(fill_matrix(matrix, n_rows, n_columns, stream), false);
    free(matrix);
    remove("test.txt");
}


TEST (FILL_MATRIX, CHECK_VALUES)
{
    size_t n_rows = 3;
    size_t n_columns = 2;
    std::ofstream test_file;
    test_file.open("test.txt");
    for (size_t i = 0; i < n_rows * n_columns; i++)
        test_file << i * 1.1 << std::endl;
    test_file.close();
    double* matrix = (double*)malloc(n_rows * n_columns * sizeof(double));
    FILE *stream = fopen("test.txt", "r");    
    ASSERT_EQ(fill_matrix(matrix, n_rows, n_columns, stream), true);
    for (size_t i = 0; i < n_rows * n_columns; i++)
        EXPECT_DOUBLE_EQ(i * 1.1, matrix[i]);
    free(matrix);
    remove("test.txt");
}




int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}