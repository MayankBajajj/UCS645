#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int A[8] = {1,2,3,4,5,6,7,8};
    int B[8] = {8,7,6,5,4,3,2,1};

    int localA[2], localB[2];
    int local_dot = 0, global_dot = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(A, 8/size, MPI_INT, localA, 8/size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, 8/size, MPI_INT, localB, 8/size, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < 8/size; i++)
        local_dot += localA[i] * localB[i];

    MPI_Reduce(&local_dot, &global_dot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("Dot Product = %d\n", global_dot);

    MPI_Finalize();
    return 0;
}