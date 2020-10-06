#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc,char *argv[]) {
  const int LIMIT = 10;

  MPI_Init(NULL, NULL);
  int world_rank;
  int world_size;
  
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int count=0;
  int partner_rank = (world_rank + 1) % 2;
  while (count < LIMIT) {
    if (world_rank == count % 2) {
      count++;
      MPI_Send(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d Enviado e incrementar ping_pong_count %d a %d\n",
             world_rank, count, partner_rank);
    } else {
      MPI_Recv(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("%d recibido ping_pong count %d de %d\n",
             world_rank,count, partner_rank);
    }
  } 
  MPI_Finalize();
}
