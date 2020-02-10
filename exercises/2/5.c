#include "mpi.h"
#include <stdio.h>

int main(argc, argv)
int argc;
char **argv;
{
	int rank, size;
    int tag, destination, count;
    int buffer; 

    tag = 1234;
    destination = 2; 
    count = 1; 
    MPI_Status status;
    MPI_Request request = MPI_REQUEST_NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if (rank == 0) {
        buffer = 9999;
        MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); 
    }

    if (rank == destination) {
        MPI_Irecv(&buffer, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &request); 

    MPI_Wait(&request, &status); 

    if (rank == 0) {
        printf("processor %d sent %d\n", rank, buffer);
    }
    if (rank == destination) {
        printf("processor %d rcv %d\n", rank, buffer);
    }

    MPI_Finalize();

	return 0;
}