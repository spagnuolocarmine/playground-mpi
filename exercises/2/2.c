#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(argc,argv) int argc; char *argv[];
{
    int numtasks, rank, dest, source, rc, count;  
    char inmsg, outmsg='X';
    MPI_Status Stat;

    char *buf = malloc(sizeof(char)); 

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Buffer_attach( buf, bufsize ); 
        MPI_Bsend(&outmsg, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Task %d: buffered send buffered, process will block on detach.\n");
        MPI_Buffer_detach( &buf, &bufsize ); 
         printf("Task %d: end buffered send.\n");
        
    } else {
        MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
        rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
        printf("Task %d: Received %d char(s) from task %d with tag %d \n",
           rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
    }
    MPI_Finalize();
}