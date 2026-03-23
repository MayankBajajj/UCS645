#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int data[100];
    int local[25];
    int local_sum = 0, global_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        for(int i = 0; i < 100; i++)
            data[i] = i + 1;
    }

    MPI_Scatter(data, 100/size, MPI_INT, local, 100/size, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < 100/size; i++)
        local_sum += local[i];

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Total Sum = %d\n", global_sum);
        printf("Average = %.2f\n", global_sum / 100.0);
    }

    MPI_Finalize();
    return 0;
}