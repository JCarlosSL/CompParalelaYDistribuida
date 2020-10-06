#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "timer.h"


int thread_count;
int counter;
sem_t count_sem;
sem_t barrier_sem;

void Usage(char* prog_name);
void *Thread_work(void* rank);

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 
   double start, finish;

   if (argc != 2)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   thread_handles =(pthread_t*) malloc (thread_count*sizeof(pthread_t));
   sem_init(&count_sem, 0, 1);
   sem_init(&barrier_sem,0,0);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }
   GET_TIME(finish);
   printf("Elapsed time = %e seconds\n", finish - start);

   sem_destroy(&count_sem);
   sem_destroy(&barrier_sem);
   free(thread_handles);
   return 0;
} 


void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}


void *Thread_work(void* rank) {
   long my_rank = (long) rank;
   int j;

      sem_wait(&count_sem);
      if (counter == thread_count - 1) {
         counter = 0;
         sem_post(&count_sem);
         for (j = 0; j < thread_count-1; j++)
            sem_post(&barrier_sem);
      } else {
         counter++;
         sem_post(&count_sem);
         sem_wait(&barrier_sem);
      }
      if (my_rank == 0) {
         printf("Todos los hilos han llgado a la barrera %d\n",counter);
         fflush(stdout);
      }

   return NULL;
}
