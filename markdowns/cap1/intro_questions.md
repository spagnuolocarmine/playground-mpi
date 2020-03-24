# Introduction Questions

?[Distributed-Memory Programming is]
-[x] allows the programmers to exploit MIMD computers.
-[ ] allows the programmers to exploit SIMD computers.
-[ ] allows the programmers to exploit SIMD computers.
-[ ] allows the programmers to exploit MIMD computers.

?What is Symmetric multiprocessing?
-[x] involves a multiprocessor computer hardware and software architecture where two or more identical processors are connected to a single, shared main memory.
-[x] involves a multiprocessor computer hardware and software architecture where two or more identical processors are connected to a multiple, shared main memory.

?[MPI is]
-[ ] a library for writing distributed-memory programs.
-[ ] a library for writing shared-memory programs.
-[x] a specification for a message-passing parallel programming model.
-[ ] a library for a message-passing parallel programming model.

?[OpenMPI is]
-[ ] a specification for the implementation of MPI.
-[x] an open-source software implementation of MPI.
-[ ] a specification for a message-passing parallel programming model.
-[ ] an open source software for a generic message-passing parallel programming model.

?[The OpenMPI Open, Portable Access Layer is responsible for]
-[x] the abstractions of OpenMPI on individual processes (versus parallel jobs).
-[ ] the abstractions of OpenMPI on individual processes (versus parallel jobs).

?[What is an MPI binding?]
-[ ] is an MPI implementation.
-[x] is the programming language support given by the standard.
-[ ] is the set of MPI API.

?[The OpenMPI Open MPI Run-Time Environment (ORTE)  is responsible for]
-[ ] the abstractions of OpenMPI on individual processes (versus parallel jobs).
-[x] the abstractions of OpenMPI to launch, monitor, and kill parallel jobs.

?[The MPI_Init function tells the MPI system to]
-[x] do all of the necessary setups.
-[ ] copy your program in the cluster.

?[The MPI_Finalize function tells the MPI system]
-[x] that we’re done using MPI.
-[ ] to delete your program in the cluster.

?[The rank of an MPI process in the MPI_COMM_WORLD communicator is a]
-[ ] floating-point number starting from 1.0.
-[ ] integer number starting from 1.
-[x] integer number starting from 0.
-[ ] integer number starting from 0.0.

@[Provide the C code using OpenMPI that write on the STDOUT the number of the processors involved in the computation.]({"stubs": ["intro_hello_world/hello_world_ex2.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world.sh"})

@[Provide the C code using OpenMPI that write on the STDOUT the rank of the process. Consider that the execution on the mpi process use the flag -np=1. The output of your program must be in the form: Hello world from processor 4ec330b6dbf8, rank 0 out of 1 processors.]({"stubs": ["intro_hello_world/hello_world_ex1.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world_one.sh"})
