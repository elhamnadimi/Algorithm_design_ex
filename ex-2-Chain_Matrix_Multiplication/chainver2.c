#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include<time.h>
 
int **m;
int **s;
/**
    m[i][j]:The matrix to store the minimum operations neede to 
            calculate Ai X Ai+1 X ... X Aj , each dimension
            of m goes from 1 to n but here for simplicity
            we have an extra first column and first row.
    s[i][j]: the matrix to store the optimal position to put
            the paranthesis to multiply Ai...j

    p[i]: stores the dimensions of matrices so that
        matrix Ai has the dimension of p[i-1][i]
    */
 
void optimal_matrix_chain_order(int *p, int n) {
    int d, i, j, k, temp, cost;
    n--;
    m = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; ++i) {
        m[i] = (int *)calloc(n, sizeof(int));
    }
 
    s = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; ++i) {
        s[i] = (int *)calloc(n, sizeof(int));
    }
    /**loop over all possible length of the chain of total length n,
    which is from l=2 to l=n-1
    */
    //L is diognal !and it starts from 2 because in diagnal 1 , all values are zero
    //becuse it is just operation for one matrix 
    //last diagnal is always n-1.
 
    for (d = 1; d < n; ++d) {
        //loop over all possible subchains of length l
        for (i = 0; i < n - d; ++i) { //Row
            j = i + d; //Col
            m[i][j] = INT_MAX;
            /**
            loop over all possible combinations to find
            minimum m[i][j] and optimal position for k
            */
            for (k = i; k < j; ++k) {
                temp = p[i] * p[k + 1] * p[j + 1];
                cost = m[i][k] + m[k + 1][j] + temp;
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}
 
void print_optimal_chain_order(int i, int j) {  // PRINT PRANTHEZATION
    if (i == j)
        // The (char) is a typecast, telling the computer to interpret
        //the 65 as acharacter, not as a number
        printf("%c", i + 65);
    else {
        printf("(");
        print_optimal_chain_order(i, s[i][j]);
        print_optimal_chain_order(s[i][j] + 1, j);
        printf(")");
    }
}
 
int main() {
    int i, j, n;
    int a1[4]  = {5, 6, 3, 1};
    int a2[8] = {5, 6, 3, 30, 1000, 7, 2, 10};
    int a3[12] = {5, 6, 3, 30, 1000, 7, 2, 10, 100, 200, 300, 400};
    int a4[15] = {5, 6, 3, 30, 1000, 7, 2, 10, 100, 200, 300, 400, 500, 600,900};
    int *p_list[4] = {a1, a2, a3, a4};
    int sizes[4] = {4, 8, 12,15};
    for (i = 0; i < 4; ++i) {
        printf("p  : [");
        n = sizes[i];
        for (j = 0; j < n; ++j) {
            printf("%d", p_list[i][j]);
            if (j < n - 1) printf(", "); else printf("]\n");
        } 
        clock_t start=clock();
        optimal_matrix_chain_order(p_list[i], n);
        clock_t end=clock();
        
        printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  

        printf("Order : ");
        print_optimal_chain_order(0, n - 2);
        printf("\nCost  : %d\n\n", m[0][n - 2]);
        for (j = 0; j <= n - 2; ++j) free(m[j]);
        free(m);
        for (j = 0; j <= n - 2; ++j) free(s[j]);
        free(s);
    }
    return 0;
}