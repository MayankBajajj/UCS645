#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int data[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    int local_max = 0, local_min = 1000;

    for(int i = 0; i < 10; i++)
    {
        data[i] = rand() % 1000;

        if(data[i] > local_max) local_max = data[i];
        if(data[i] < local_min) local_min = data[i];
    }

    int global_max, global_min;

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Global Max = %d\n", global_max);
        printf("Global Min = %d\n", global_min);
    }

    MPI_Finalize();
    return 0;
}