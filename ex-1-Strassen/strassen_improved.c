#include <stdlib.h>

#include "matrix.h"


void sum_matrix_blocks(float **C,
                       const size_t C_row,
                       const size_t C_col,
                       float ** A,
                       const size_t A_row,
                       const size_t A_col,
                       float ** B,
                       const size_t B_row,
                       const size_t B_col,
                       const size_t n);

void sub_matrix_blocks(float **C,
                       const size_t C_row,
                       const size_t C_col,
                       float ** A,
                       const size_t A_row,
                       const size_t A_col,
                       float ** B,
                       const size_t B_row,
                       const size_t B_col,
                       const size_t n);

void naive_aux(float **C, const size_t C_row, const size_t C_col,
               float **A, const size_t A_row, const size_t A_col,
               float **B, const size_t B_row, const size_t B_col,
               const size_t n);
  /*
  using the (M2X,MX2) submatrix as the auxiliary matrix to pass recursively.
  The other 3 submatrices (M1X,MX1), (M1X,MX2), (M2X,MX1) are the auxiliary matrices used to store
  the temporary matrices Pi and Si.
  exploiting some temporary unused submatrices of C to store Pi and Si.
  */

void strassen_aux_improved(float **C, const size_t C_row, const size_t C_col,
                  float **A, const size_t A_row, const size_t A_col,
                  float **B, const size_t B_row, const size_t B_col,
 		  float **M, const size_t buffer_row, const size_t buffer_col, //added an auxiliary matrix
                  const size_t n)

{
  if (n < (1<<6)) {  // naive mul for very small block!
    naive_aux(C, C_row, C_col,
              A, A_row, A_col,
              B, B_row, B_col,
              n);
    return;
  }

  const size_t n2=n/2;

  const size_t C1X = C_row;
  const size_t C2X = C_row + n2; //Divide matrices A and B in 4 sub-matrices of size N/2 x N/2 
  const size_t CX1 = C_col;
  const size_t CX2 = C_col + n2;

  const size_t A1X = A_row;
  const size_t A2X = A_row + n2;
  const size_t AX1 = A_col;
  const size_t AX2 = A_col + n2;

  const size_t B1X = B_row;
  const size_t B2X = B_row + n2;
  const size_t BX1 = B_col;
  const size_t BX2 = B_col + n2;

  const size_t M1X = buffer_row;
  const size_t M2X = buffer_row + n2;
  const size_t MX1 = buffer_col;
  const size_t MX2 = buffer_col + n2;

    /*  Devide matrix into sub blocks: 
    C11 = A11*B11 + A12*B21*/

    // C11 = (P5 + P4) - P2 + P6
    // compute P6
  	// P6 = S7 x S8
  	// where S7 = A12 - A22 and S8 = B21 + B22

    sub_matrix_blocks(C, C2X, CX2,  //S7 = A12 - A22 
        	            A,A1X,AX2,
        	            A,A2X,AX2,
        	            n2);

  	sum_matrix_blocks(C, C1X, CX2,  //S8 = B21 + B22
        	            B,B2X,BX1,
        	            B,B2X,BX2,
        	            n2);

  	strassen_aux_improved(M, M1X, MX1, //P6  // for multiplication we call again strasen improved
        	     C, C2X, CX2, //S7
        	     C, C1X, CX2, //S8
      		     M,M2X,MX2,   
        	     n2);

    // compute P2
  	// P2 = S2 x B22
  	// where S2 = A11 + A12
 	 sum_matrix_blocks(C, C2X, CX2, //S2
 	                   A,A1X,AX1,
 	                   A,A1X,AX2,
 	                   n2);

 	 strassen_aux_improved(C, C1X, CX2, //P2
  	             C, C2X, CX2, //S2
  	             B, B2X, BX2, //B22
		     M,M2X,MX2,
  	             n2);

  // compute P5
  	// P5 = S5 x S6
  	// where S5 = A11 + A22 and S6 = B11 + B22
  	sum_matrix_blocks(C, C2X, CX2, //S5
  	                  A,A1X,AX1,
  	                  A,A2X,AX2,
  	                  n2);

 
  	sum_matrix_blocks(C, C2X, CX1, //S6
        	            B,B1X,BX1,
        	            B,B2X,BX2,
        	            n2);

  	strassen_aux_improved(M, M1X, MX2, // P5
		       C, C2X, CX2, //S5
        	       C, C2X, CX1, //S6 
		       M,M2X,MX2,   
        	       n2);

  //compute P4
  	// P4 = A22 x S4
  	// where S4 = B21 - B11
  	sub_matrix_blocks(C, C2X, CX2, //S4
        	            B,B2X,BX1,
        	            B,B1X,BX1,
        	            n2);

  	strassen_aux_improved(M, M2X, MX1, // P4
        	       A, A2X, AX2,
        	       C, C2X, CX2, //S4
		       M,M2X,MX2,
        	       n2);

  // P4 + P5
  sum_matrix_blocks(C, C1X, CX1,
  	            M, M1X, MX2, //P5
  	            M, M2X, MX1, //P4
  	            n2);

  // (P4 + P5) - P2
  sub_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    C, C1X, CX2, //P2
                    n2);

  // ((P4 + P5) - P2) + P6
  sum_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    M, M1X, MX1, //P6
                    n2);



  /// C12 = P1 + P2

  // compute P1
 	 // P1 = A11 x S1
  	 // where S1 = B12 - B22
  	sub_matrix_blocks(C, C2X, CX1, //S1
        	          B, B1X,BX2,
        	          B, B2X,BX2,
        	          n2);

	strassen_aux_improved(C, C2X, CX2, //P1
	             A, A1X, AX1,
	             C, C2X, CX1, //S1
		     M, M2X, MX2,
	             n2);


        sum_matrix_blocks(C, C1X, CX2,
                          C, C2X, CX2, //P1
                          C, C1X, CX2, //P2
                          n2);


  // C21 = P3 + P4

  // compute P3
 	 // P3 = S3 x B11
 	 // where S3 = A21 + A22
 	 sum_matrix_blocks(C, C2X, CX1, //S3
  	                   A, A2X, AX1,
  	                   A, A2X, AX2,
  	                   n2);

  	 strassen_aux_improved(M, M1X, MX1, //P3
        	      C, C2X, CX1, //S3
        	      B, B1X, BX1,
		      M,M2X,MX2,
        	      n2);


         sum_matrix_blocks(C, C2X, CX1,
                           M, M1X, MX1, //P3
                           M, M2X, MX1, //P4
                           n2);



  // C22 = P5 + P1 - P3 - P7

  // P1 + P5
  sum_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2, //P1
                    M, M1X, MX2, //P5
                    n2);

  // (P5 + P1) - P3
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    M, M1X, MX1, //P3
                    n2);

  //compute P7
  	// P7 = S9 x S10
  	// where S9 = A11 - A21 and S10 = B11 + B12
 	 sub_matrix_blocks( M, M1X, MX1, //S9
        	            A,A1X,AX1,
        	            A,A2X,AX1,
        	            n2);

  	 sum_matrix_blocks( M, M1X, MX2, //S10
        	            B,B1X,BX1,
        	            B,B1X,BX2,
        	            n2);

  	 strassen_aux_improved(M, M2X, MX1, //P7
        	      M, M1X, MX1, //S9
        	      M, M1X, MX2, //S10
		      M,M2X,MX2,
        	      n2);

  // ((P5 + P1) - P3) - P7
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    M, M2X, MX1, //P7
                    n2);

}

void strassen_improved(float **C, float **A, float **B, const size_t n)
{
  float **M = allocate_matrix(n,n); // allocate auxiliary matrix
  strassen_aux_improved(C, 0, 0, A, 0, 0, B, 0, 0, M, 0, 0, n);
  deallocate_matrix(M,n); // free auxiliary matrix
}
