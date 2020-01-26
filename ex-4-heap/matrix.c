#include <stdlib.h>
#include <stdio.h>
#define MAX_ELEM_VALUE 25


int **allocate_int_matrix(const size_t rows,
                          const size_t cols)
{
    int **A=(int **)malloc(sizeof(int *)*rows);

    for (size_t i=0; i<rows; i++) {
        A[i]=(int *)malloc(sizeof(int)*cols);
    }

    return A;
}

void deallocate_int_matrix(int **A, const size_t rows)
{
    for (size_t i=0; i<rows; i++) {
        free(A[i]);
    }

    free(A);
}



void randomly_fill_int_matrix(int **A, const size_t A_rows, const size_t A_cols, const size_t max_value)
{
    for (size_t i=0; i< A_rows; i++) {
        for (size_t j=0; j< A_cols; j++) {
            A[i][j]=(int)(rand()%(2*max_value)-max_value);
        }
    }
}
