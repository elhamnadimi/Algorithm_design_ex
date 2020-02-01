#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<time.h>

/**
This is dynamice programming approach to solve the matrix chain problem,
giving an n number of matrices to multiply determine the best ordering of
the multiplication to do the minimum number of operation.

For a detailed explanation refer to:
https://home.cse.ust.hk/~dekai/271/notes/L12/L12.pdf
*/


int MatrixChainOrder(int p[], int n)
{
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


	int m[n][n];
	int s[n][n];
	int i, j, k, l, q;
	// operations for one matrix is zero
	for(i = 0; i < n; ++i)
		m[i][i] = 0;
	/**loop over all possible length of the chain of total length n,
	which is from l=2 to l=n-1
	*/
	//L is diognal !and it starts from 2 because in diagnal 1 , all values are zero
	//becuse it is just operation for one matrix 
	//last diagnal is always n-1.

	for(l = 2; l < n; ++l)
	{
		//loop over all possible subchains of length l
		for(i = 0; i < n-l+1; ++i)
		{
			j = i + l -1;  // col
			m[i][j] = INT_MAX;
			/**
			loop over all possible combinations to find
			minimum m[i][j] and optimal position for k
			*/
			for(k = i; k < j; ++k)
			{
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if(q < m[i][j])
				{
					m[i][j] = q;
					printf("s[%d, %d] = %d\n", i, j, k);
				}
			}
		}
	}

	return m[1][n-1];

}

int main()
{
	int arr[] = {5, 6, 3, 1};
	int size = sizeof(arr) / sizeof(arr[0]);
	clock_t start=clock();
	int minOps = MatrixChainOrder(arr, size);
		clock_t end=clock();

	printf("Minumum number of multiplication: %d\n", minOps);
	printf("time passed[s] %lf \n", (double)(end-start)/CLOCKS_PER_SEC );  


	return 0;
}