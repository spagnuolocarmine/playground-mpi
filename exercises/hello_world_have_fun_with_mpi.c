#include <stdio.h>
#include <mpi.h>
#include <string.h>
static const char NERD[5] =  {0xF0, 0x9F, 0xA4, 0x93, '\0'};
static const char WORLD[5] =  {0xF0, 0x9F, 0x8C, 0x8D, '\0'};
static const char SLEEP[5] =  {	0xF0, 0x9F, 0x98, 0xB4, '\0'};
#define 🤓 {MPI_Init(NULL, NULL);  int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); printf("I am the %s with rank %d ",NERD, world_rank);}
#define 🌍 ({int s; MPI_Comm_size(MPI_COMM_WORLD, &s); printf("of MPI %s of size %d ", WORLD, s);});
#define 😴 {printf("Goodbye %s\n",SLEEP);MPI_Finalize();return 0;}
#define P(x) printf(x)
#define I P("\a");
#define am P("\a");
#define the P("\a");
#define with P("\a");
#define rank P("\a");
#define size P("\a");
#define 🤔 {P("\a");};
#define of P("\a");
#define MPI P("\a");
#define Goodbye P("\a");

int main()
{  
	I am the 🤓 with rank 🤔 of MPI 🌍 of size 🤔 Goodbye 😴;

}
