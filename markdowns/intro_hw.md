# GETTING STARTED

Perhaps the first program that many of us saw was some variant of the “hello, world”
program in Kernighan and Ritchie’s classic text.

```c
#include <stdio.h> 
int main(void) {
	printf("hello, world\n"); 
	return 0;
}
```

Let’s write a program similar to “hello, world” that makes some use of MPI. Instead of having each process simply print a message, we’ll designate one process to do the output, and the other processes will send it messages, which it will print.

In parallel programming, it’s common (one might say standard) for the processes to be identified by nonnegative integer ranks. So if there are p processes, the processes will have ranks 0,1,2,..., p−1. For our parallel “hello, world,” let’s make process 0 the designated process, and the other processes will send it messages.

@[Hello World]({"stubs": ["intro_hello_world/hello_world.c"]})

## Compilation and execution

The details of compiling and running the program depend on your system, so you may need to check with a local expert. However, recall that when we need to be explicit, we’ll assume that we’re using a text editor to write the program source, and the command line to compile and run. Many systems use a command called _mpicc_ for compilation:



```bash
$ mpicc −g −Wall −o mpi hello mpi hello.c
```

Typically, mpicc is a script that’s a wrapper for the C compiler. A wrapper script is a script whose main purpose is to run some program. In this case, the program is the C compiler. However, the wrapper simplifies the running of the compiler by telling it where to find the necessary header files and which libraries to link with the object file.

Many systems also support program startup with mpiexec or mpirun:

```bash
$ mpirun −n <number of processes> ./mpi hello
```

So to run the program with one process, we’d type


```bash
$ mpirun −n 1 ./mpi hello
```

@[Hello World]({"stubs": ["intro_hello_world/hello_world.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world_one.sh"})

and to run the program with four processes, we’d type

```bash
$ mpiexec −n 4 ./mpi hello
```

@[Hello World]({"stubs": ["intro_hello_world/hello_world.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world.sh"})

How do we get from invoking mpiexec to one or more lines of greetings? The mpiexec command tells the system to start <number of processes> instances of our <mpi hello> program. It may also tell the system which core should run each instance of the program. After the processes are running, the MPI implementation takes care of making sure that the processes can communicate with each other.


