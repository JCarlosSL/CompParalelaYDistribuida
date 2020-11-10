#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const int RMAX = 10000000;

int thread_count;

void Usage(char* prog_name);
void Get_args(int argc, char* argv[], int* n_p);
void Generate_list(int a[], int n);
void Odd_even(int a[], int n);

/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   int  n;
   int* a;
   double start, finish;

   Get_args(argc, argv, &n);
   a = (int*)malloc(n*sizeof(int));

   Generate_list(a, n);

   start = omp_get_wtime();
   Odd_even(a, n);  
   finish = omp_get_wtime();

   printf("Elapsed Time = %f seconds\n", finish - start);

   free(a);
   return 0;
}

void Usage(char* prog_name) {
   fprintf(stderr, "usage:   %s <thread count> <n>\n", prog_name);
   fprintf(stderr, "   n:   numero de elementos de la lista\n");
}


void Get_args(int argc, char* argv[], int* n_p) {
   if (argc != 3 ) {
      Usage(argv[0]);
      exit(0);
   }
   thread_count = strtol(argv[1], NULL, 10);
   *n_p = strtol(argv[2], NULL, 10);

   if (*n_p <= 0) {
      Usage(argv[0]);
      exit(0);
   }
}

void Generate_list(int a[], int n) {
   int i;

   srandom(1);
   for (i = 0; i < n; i++)
      a[i] = random() % RMAX;
}


void Odd_even(int a[], int n) {
   int phase, i, tmp;

#  pragma omp parallel num_threads(thread_count) \
      default(none) shared(a, n) private(i, tmp, phase)
   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
#        pragma omp for 
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
#        pragma omp for 
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
}
