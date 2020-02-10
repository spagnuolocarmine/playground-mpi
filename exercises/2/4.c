#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
   
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
   
    enum role_ranks { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        {
            printf("MPI process %d hits the barrier to wait for the matching MPI_Recv to be posted.\n", my_rank);
            MPI_Barrier(MPI_COMM_WORLD);
            printf("The barrier unlocked, which means the MPI_Recv is already posted so the MPI_Rsend can be issued.\n");
 
            int buffer_sent = 12345;
            printf("MPI process %d sends value %d.\n", my_rank, buffer_sent);
            MPI_Rsend(&buffer_sent, 1, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
            break;
        }
        case RECEIVER:
        {
            int received;
            MPI_Request request;
            MPI_Irecv(&received, 1, MPI_INT, SENDER, 0, MPI_COMM_WORLD, &request);
 
            printf("MPI process %d issued the MPI_Irecv, moved on and hit the barrier.\n", my_rank);
            MPI_Barrier(MPI_COMM_WORLD);
 
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            printf("MPI process %d receives value %d.\n", my_rank, received);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}