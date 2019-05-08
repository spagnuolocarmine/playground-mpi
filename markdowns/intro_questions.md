# Introduction Questions

?[Distributed-Memory Programming is]
-[x] allows the programmers to exploit MIMD computers.
-[ ] allows the programmers to exploit SIMD computers.
-[ ] allows the programmers to exploit SIMD computers.
-[ ] allows the programmers to exploit MIMD computers.

?[MPI is]
-[ ] a library for writing distributed memory programs.
-[ ] a library for writing shared memory programs.
-[x] a specification for a message-passing parallel programming model.
-[ ] a library for a message-passing parallel programming model.

?[OpenMPI is]
-[ ] a specification for an implementation of MPI.
-[x] an open source software implementation of MPI.
-[ ] a specification for a message-passing parallel programming model.
-[ ] a open source software for a generic message-passing parallel programming model.

?[The OpenMPI Open, Portable Access Layer is responsible for]
-[x] the abstractions of OpenMPI on individual processes (versus parallel jobs).
-[ ] the abstractions of OpenMPI on individual processes (versus parallel jobs).

?[The OpenMPI Open MPI Run-Time Environment (ORTE)  is responsible for]
-[ ] the abstractions of OpenMPI on individual processes (versus parallel jobs).
-[x] the abstractions of OpenMPI to launch, monitor, and kill parallel jobs.

@[Provide the C code using OpenMPI that write on the STDOUT the rank of the process. Consider that the execution on the mpi process use the flag -np=1.]({"stubs": ["intro_hello_world/hello_world_ex1.c"], "command": "/bin/bash /project/target/intro_hello_world/hello_world_one.sh"})
