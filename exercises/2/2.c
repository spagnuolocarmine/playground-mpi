#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(argc,argv) int argc; char *argv[];
{
    int numtasks, rank, dest, source, rc, count;  
    char *inmsg, outmsg='This is my testing message';
    MPI_Status Stat;
    int bufsize = sizeof(outmsg);
    char *buf = malloc(bufsize); 
    *inmsg = malloc(100*sizeof(char));

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Buffer_attach( buf, bufsize ); 
        int time = MPI_Wtime();
        MPI_Bsend(&outmsg, strlen(outmsg), MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Task %d: buffered send (1) buffered , process will block on detach. Time: %1.2f\n",rank, MPI_Wtime() - time);
        MPI_Buffer_detach( &buf, &bufsize ); 
        time = MPI_Wtime();
        MPI_Bsend(&outmsg, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Task %d: buffered send (2), process may will block here. Time: %1.2f\n",rank, MPI_Wtime() - time);
        
    } else {
        MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
        rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
        printf("Task %d: Received %d char(s) from task %d with tag %d \n",
           rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
        MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
        rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
        printf("Task %d: Received %d char(s) from task %d with tag %d \n",
           rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
    }
    MPI_Finalize();
}