# MPI programs

Let’s take a closer look at the program. The first thing to observe is that this is a C program. For example, it includes the standard C header files stdio.h and string.h. It also has the main function just like any other C program. 

```c
#include <stdio.h>
#include <string.h> 
#include <mpi.h>
int main(int argc, char* argv[]){
	/*No MPI call before this*/
	MPI_Init(&argc,&argv);
	...
	MPI_Finalize();
	/*No MPI call after this*/
	...
	return 0;
}
```

However, there are many parts of the program which are new. Line 3 includes the mpi.h header file. This contains prototypes of MPI functions, macro definitions, type definitions, and so on; it contains all the definitions and declarations needed for compiling an MPI program.

The second thing to observe is that all of the identifiers defined by MPI start with the string **MPI\_**.

The first letter following the underscore is capitalized for function names and MPI-defined types. All of the letters in MPI-defined macros and con- stants are capitalized, so there’s no question about what is defined by MPI and what’s defined by the user program.

#### MPI\_Init and MPI\_Finalize

The call to MPI Init tells the MPI system to do all of the necessary setup. For example, it might allocate storage for message buffers, and it might decide which process gets which rank. As a rule of thumb, no other MPI functions should be called before the program calls MPI Init. Its syntax is

```c
int MPI Init(
	int∗ argc p /∗ in/out ∗/, 
	char∗∗∗ argv p /∗ in/out ∗/);
```

The arguments, argc p and argv p, are pointers to the arguments to main, argc, and argv. However, when our program doesn’t use these arguments, we can just pass NULL for both. Like most MPI functions, MPI Init returns an int error code, and in most cases, we’ll ignore these error codes.

This means that MPI is responsible for spawn the arguments of the main function to each MPI process.

The call to MPI Finalize tells the MPI system that we’re done using MPI, and that any resources allocated for MPI can be freed. The syntax is quite simple.


## Communication Abstraction


In MPI a communicator is a collection of processes that can send messages to each other. One of the purposes of MPI Init is to define a communicator that consists of all of the processes started by the user when she started the program. This communicator is called MPI\_COMM\_WORLD.  Their syntax is

```c
int MPI_Comm_size( 
	MPI_Comm comm /*in*/,
	int∗ comm_sz_p /*out*/);

int MPI_Comm_rank( 
	MPI_Comm comm /*in*/,
	int∗ my_rank /*out*/);
```

For both functions, the first argument is a communicator and has the special type defined by MPI for communicators, MPI\_Comm. MPI\_Comm\_size returns in its second argument the number of processes in the communicator, and MPI\_Comm\_rank returns in its second argument the calling process’ rank in the communicator. We’ll often use the variable comm sz for the number of processes in MPI\_COMM\_WORLD, and the variable my rank for the process rank.

### The MPI\_COMM\_WORLD

![MPICOMMWORLD](/img/mpi-comm-world.png)

Execute the program and notice the number of processors and the given rank to each one. 

The following example uses 4 processes.
@[Hello World]({"stubs": ["intro_hello_world/hello_world.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world.sh"})

