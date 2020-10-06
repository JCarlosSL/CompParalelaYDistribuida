 /* Compile:
 *    gcc -g -Wall -o pth_busy_bar pth_busy_bar.c -lpthread
 * Usage:
 *    ./pth_busy_bar <thread_count>
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

int counter;
int thread_count;
pthread_mutex_t barrier_mutex;

void Usage(char* prog_name);
void *Thread_work(void* rank);

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 
   double start, finish;

   if (argc != 2) Usage(argv[0]);
   
   //cantidad de hilos
   thread_count = strtol(argv[1], NULL, 10);

   //reservación de memoria
   thread_handles =(pthread_t*) malloc (thread_count*sizeof(pthread_t));
   counter=0;
   pthread_mutex_init(&barrier_mutex, NULL);

   GET_TIME(start);
   
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }
   
   GET_TIME(finish);
   printf("Elapsed time = %e seconds\n", finish - start);

   pthread_mutex_destroy(&barrier_mutex);
   free(thread_handles);
   return 0;
}  /* main */


void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */


void *Thread_work(void* rank) {
   long my_rank = (long) rank; 
      
   pthread_mutex_lock(&barrier_mutex);
   counter++;
   pthread_mutex_unlock(&barrier_mutex);
   while (counter < thread_count);
   if (my_rank == 0) {
       printf("Todos los hilos estan en la barrera, el contador es %d\n",counter);
       fflush(stdout);
   }

   return NULL;
}  
