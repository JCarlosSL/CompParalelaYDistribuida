/* File:     
 *     omp_mat_vect.c 
 *
 *
 * Purpose:  
 *     Computes a parallel matrix-vector product.  Matrix
 *     is distributed by block rows.  Vectors are distributed by 
 *     blocks.  Unless the DEBUG flag is turned on this version 
 *     uses a random number generator to generate A and x.
 *
 * Input:
 *     None unless compiled with DEBUG flag.
 *     With DEBUG flag, A, x
 *
 * Output:
 *     y: the product vector
 *     Elapsed time for the computation
 *
 * Compile:  
 *    gcc -g -Wall -fopenmp -o omp_mat_vect omp_mat_vect.c
 * Usage:
 *    omp_mat_vect <thread_count> <m> <n>
 *
 * Notes:  
 *     1.  Storage for A, x, y is dynamically allocated.
 *     2.  Number of threads (thread_count) should evenly divide both 
 *         m and n.  The program doesn't check for this.
 *     3.  We use a 1-dimensional array for A and compute subscripts
 *         using the formula A[i][j] = A[i*n + j]
 *     4.  Distribution of A, x, and y is logical:  all three are 
 *         globally shared.
 *     5.  DEBUG compile flag will prompt for input of A, x, and
 *         print y
 *     6.  Uses the OpenMP library function omp_get_wtime() to
 *         return the time elapsed since some point in the past
 *
 * IPP:    Section 5.9 (pp. 253 and ff.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* Serial functions */
void Get_args(int argc, char* argv[], int* thread_count_p, 
      int* m_p, int* n_p);
void Usage(char* prog_name);
void Gen_matrix(double A[], int m, int n);
void Read_matrix(char* prompt, double A[], int m, int n);
void Gen_vector(double x[], int n);
void Read_vector(char* prompt, double x[], int n);
void Print_matrix(char* title, double A[], int m, int n);
void Print_vector(char* title, double y[], double m);

/* Parallel function */
void Omp_mat_vect(double A[], double x[], double y[],
      int m, int n, int thread_count);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   int     thread_count;
   int     m, n;
   double* A;
   double* x;
   double* y;

   Get_args(argc, argv, &thread_count, &m, &n);

   A = (double *)malloc(m*n*sizeof(double));
   x = (double *)malloc(n*sizeof(double));
   y = (double *)malloc(m*sizeof(double));
   
   Omp_mat_vect(A, x, y, m, n, thread_count);

   free(A);
   free(x);
   free(y);

   return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get command line args
 * In args:   argc, argv
 * Out args:  thread_count_p, m_p, n_p
 */
void Get_args(int argc, char* argv[], int* thread_count_p, 
      int* m_p, int* n_p)  {

   if (argc != 4) Usage(argv[0]);
   *thread_count_p = strtol(argv[1], NULL, 10);
   *m_p = strtol(argv[2], NULL, 10);
   *n_p = strtol(argv[3], NULL, 10);
   if (*thread_count_p <= 0 || *m_p <= 0 || *n_p <= 0) Usage(argv[0]);

}  /* Get_args */

void Usage (char* prog_name) {
   fprintf(stderr, "usage: %s <thread_count> <m> <n>\n", prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:  Omp_mat_vect
 * Purpose:   Multiply an mxn matrix by an nx1 column vector
 * In args:   A, x, m, n, thread_count
 * Out arg:   y
 */
void Omp_mat_vect(double A[], double x[], double y[],
                    int m, int n, int thread_count) {
   int i, j;
   double start, finish, elapsed;

   start = omp_get_wtime();
#  pragma omp parallel for num_threads(thread_count)  \
      default(none) private(i, j)  shared(A, x, y, m, n)
   for (i = 0; i < m; i++) {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
         y[i] += A[i*n+j]*x[j];
   }
   finish = omp_get_wtime();
   elapsed = finish - start;
   printf("Elapsed time = %e seconds\n", elapsed);

}  /* Omp_mat_vect */

