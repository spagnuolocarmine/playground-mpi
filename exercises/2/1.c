#include "mpi.h"
#include <stdio.h>

int main(argc,argv) int argc; char *argv[];
{
    int numtasks, rank, dest, source, rc, count;  
    char inmsg, outmsg='x';
    MPI_Status Stat;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Send(&outmsg, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&outmsg, 1, MPI_CHAR, 2, 2, MPI_COMM_WORLD);
        MPI_Send(&outmsg, 1, MPI_CHAR, 3, 3, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
        rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
        printf("Task %d: Received %d char(s) from task %d with tag %d \n",
           rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
    }
    MPI_Finalize();
}