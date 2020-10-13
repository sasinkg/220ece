/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA, double *matrixB, double *matrixC,int m,int k,int n)
{
//YOUR CODE HERE
for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
         matrixC[i][j] = 0;
      }
   }

for (int i = 0; i < m; ++i) {
    for (int a = 0; a < k; ++a) {
        for (int o = 0; o < n; ++o) {
            matrixC[i][a] += matrixA[i][o] * matrixB[o][a];
        }
    }
}
}

