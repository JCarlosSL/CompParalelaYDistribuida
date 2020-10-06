#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

const int MAX_THREADS = 1024;
const int MSG_MAX = 100;

int thread_count;
char** messages;
sem_t* semaphores;

void Usage(char* prog_name);
void *Send_msg(void* rank);

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

   //reservando memoria
   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
   messages = (char**)malloc(thread_count*sizeof(char*));
   semaphores = (sem_t*)malloc(thread_count*sizeof(sem_t));
   
   for (thread = 0; thread < thread_count; thread++){
      messages[thread] = NULL;
      sem_init(&semaphores[thread],0,0);
   }


   // Creacion de threads
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Send_msg, (void*) thread);

   // Ejecucion de threads
   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }

   //limpiando memoria
   for (thread = 0; thread < thread_count; thread++){
      free(messages[thread]);
      sem_destroy(&semaphores[thread]);
   }
   free(messages);
   free(semaphores);
   free(thread_handles);
   return 0;
}  

void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}


void *Send_msg(void* rank) {
   long my_rank = (long) rank;
   long dest = (my_rank + 1) % thread_count;

   //long source = (my_rank + thread_count - 1) % thread_count;
   char* my_msg = (char*) malloc(MSG_MAX*sizeof(char));

   sprintf(my_msg, "Este es un mensaje para %ld de %ld", dest, my_rank);
   messages[dest] = my_msg;

   sem_post(&semaphores[dest]);

   sem_wait(&semaphores[my_rank]);
   printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
   return NULL;
}  
