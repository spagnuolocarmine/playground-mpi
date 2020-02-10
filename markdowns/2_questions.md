# Point-to-Poit Communication Questions

?[What does it mean that an operation is posted?]
-[x] a send or receive operation is started.
-[ ] a send or receive operation is ended.
-[ ] a send or receive operation is ended with an error.

?[MPI manages system memory..]
-[ ] that is used for sending  and  receiving messages.
-[x] that is used for buffering messages and for storing internal representations of various MPI objects such as groups, communicators, datatypes, etc. 
-[ ] that is used for allocate the user memory.

?[How many buffer MPI defines?]
-[ ] 2, application and internal.
-[x] 1, application.
-[ ] 1, internal.
-[ ] 3, application, internal and special.


?[What does the MPI_Buffer_detach do?]
-[x] removes the buffer currently attached to the MPI buffer space.
-[ ] removes the buffer currently attached to the user buffer space.
-[ ] removes the buffer currently attached to the MPI and user buffer space.


?[MPI_INT?]
-[x] is a datatype of MPI.
-[ ] is the int definition of an integer value in C.


?[What is a MPI program?]
-[ ] An MPI program consists of one MPI process and a number of child processes.
-[x] An MPI program consists of autonomous processes, executing their own code.


@[Provide the C code using OpenMPI that write on the STDOUT the number of the processors involved in the computation.]({"stubs": ["intro_hello_world/hello_world_ex2.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world.sh"})

@[Provide the C code using OpenMPI that write on the STDOUT the rank of the process. Consider that the execution on the mpi process use the flag -np=1. The output of your program must be in the form: Hello world from processor 4ec330b6dbf8, rank 0 out of 1 processors.]({"stubs": ["intro_hello_world/hello_world_ex1.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world_one.sh"})
