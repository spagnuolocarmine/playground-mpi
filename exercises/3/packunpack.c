#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h" 

#define MASTER 0
#define STRLEN 25

int main(int argc, char* argv[])
{
  int rank;                    
  int size;                   
  int position;                 

  char message[BUFSIZ];       

  float  value;          //VALUE TO SEND
  char   name[STRLEN];  //ASSIGNED NAME
  int    param;   //ADDITIONAL PARAM

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  if (rank == MASTER) {
  
    value = 10;
    sprintf(name, "My Name");
    param = 1;

    position = 0;
    /* now let's pack all those values into a single message */
    MPI_Pack(&value, 1, MPI_FLOAT, message, BUFSIZ,
	     &position, MPI_COMM_WORLD);
    /* position has been incremented to first free byte in the message.. */
    MPI_Pack(name, STRLEN, MPI_CHAR, message, BUFSIZ,
	     &position, MPI_COMM_WORLD);
    /* position has been incremented again.. */
    MPI_Pack(&param, 1, MPI_INT, message, BUFSIZ,
	     &position, MPI_COMM_WORLD);

    MPI_Send(message, BUFSIZ, MPI_PACKED, 1, 1, MPI_COMM_WORLD);
  }
  else {

    MPI_Recv(message, BUFSIZ, MPI_PACKED, 0, 1, MPI_COMM_WORLD, NULL);

    position = 0;
    MPI_Unpack(message, BUFSIZ, &position, &value, 1,
	       MPI_FLOAT, MPI_COMM_WORLD);
    /* Note that we must know the length of string to expect here!  */
    MPI_Unpack(message, BUFSIZ, &position, name, STRLEN,
	       MPI_CHAR, MPI_COMM_WORLD);
    MPI_Unpack(message, BUFSIZ, &position, &param, 1,
	       MPI_INT, MPI_COMM_WORLD);

    printf("rank %d:\t%d %.1f %s\n", rank, param, value, name); 
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}