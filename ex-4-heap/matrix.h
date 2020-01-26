#ifndef __MATRIX__

#include <stdlib.h>
#include <stdio.h>



int **allocate_int_matrix(const size_t rows, const size_t cols);

void deallocate_int_matrix(int **A, const size_t rows);

void randomly_fill_int_matrix(int **A, const size_t A_rows, const size_t A_cols, const size_t max_value);



#endif // __MATRIX__