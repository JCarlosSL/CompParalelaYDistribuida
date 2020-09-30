#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int no_comm = MPI::COMM_WORLD.Get_size();
    if (no_comm != 2)
        return 1;

    int maximum  = std::atoi(argv[1]);
    int selfrank = MPI::COMM_WORLD.Get_rank();

    int count = 0;

    // Send the first message 
    if (selfrank == 0)
        MPI::COMM_WORLD.Send(&count, 1, MPI::INT,  1, 0);

    while (count < maximum) {
        MPI::COMM_WORLD.Recv(&count, 1, MPI::INT, selfrank ^ 1, 0);
        if (selfrank == 0)
            printf("%d\n", count);
        count += 1;
        MPI::COMM_WORLD.Send(&count, 1, MPI::INT, selfrank ^ 1, 0);
    }

    // Receive the last message
    if (selfrank == (maximum & 1)) {
        MPI::COMM_WORLD.Recv(&count, 1, MPI::INT, selfrank ^ 1, 0);
    }

    MPI::Finalize();
}