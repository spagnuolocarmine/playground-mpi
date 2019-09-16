# Distributed-Memory Programming with MPI

Recall that the world of parallel multiple instruction, multiple data, or MIMD, computers is, for the most part, divided into distributed-memory and shared-memory systems. From a programmer’s point of view, a distributed-memory system consists of a collection of core-memory pairs connected by a network, and the memory associated with a core is directly accessible only to that core. On the other hand, from a programmer’s point of view, a shared-memory system consists of a collection of cores connected to a globally accessible memory, in which each core can have access to any memory location. 

![mpimodel](/img/mpimodel.png) 


Recall that in message-passing programs, a program running on one core-memory pair is usually called a process, and two processes can communicate by calling functions: one process calls a send function and the other calls a receive function. The implementation of message-passing that we’ll be using is called MPI, which is an abbreviation of Message-Passing Interface. MPI is not a new programming language. It defines a library of functions that can be called from C, C++, and Fortran programs. We’ll learn about some of MPI’s different send and receive functions. We’ll also learn about some “global” communication functions that can involve more than two processes. These functions are called collective communications. In the process of learning about all of these MPI functions, we’ll also learn about some of the fundamental issues involved in writing message-passing programs–issues such as data partitioning and I/O in distributed-memory systems. We’ll also revisit the issue of parallel program performance.

# What is MPI?

- M P I = Message Passing Interface
- MPI is a specification for the developers and users of message passing libraries. By itself, it is NOT a library - but rather the specification of what such a library should be.
- MPI primarily addresses the message-passing parallel programming model: data is moved from the address space of one process to that of another process through cooperative operations on each process.
- Simply stated, the goal of the Message Passing Interface is to provide a widely used standard for writing message passing programs. The interface attempts to be:
	- _Practical_
	- _Portable_
	- _Efficient_
	- _Flexible_
- The MPI standard has gone through a number of revisions, with the most recent version being MPI-3.x
- Interface specifications have been defined for C and Fortran90 language bindings:
	- C++ bindings from MPI-1 are removed in MPI-3
	- MPI-3 also provides support for Fortran 2003 and 2008 features
- Actual MPI library implementations differ in which version and features of the MPI standard they support. Developers/users will need to be aware of this.

### Reasons for Using MPI:

- **Standardization** - MPI is the only message passing library that can be considered a standard. It is supported on virtually all HPC platforms. 
- **Practically**, it has replaced all previous message passing libraries.
- **Portability** - There is little or no need to modify your source code when you port your application to a different platform that supports (and is compliant with) the MPI standard.
- **Performance Opportunities** - Vendor implementations should be able to exploit native hardware features to optimize performance. Any implementation is free to develop optimized algorithms.
- **Functionality** - There are over 430 routines defined in MPI-3, which includes the majority of those in MPI-2 and MPI-1. 
- **Availability** - A variety of implementations are available, both vendor and public 

### History and Evolution:

- MPI has resulted from the efforts of numerous individuals and groups that began in 1992. Some history:
- 1980s - early 1990s: Distributed memory, parallel computing develops, as do a number of incompatible software tools for writing such programs - usually with tradeoffs between portability, performance, functionality and price. Recognition of the need for a standard arose.
MPI Evolution
- Apr 1992: Workshop on Standards for Message Passing in a Distributed Memory Environment, sponsored by the Center for Research on Parallel Computing, Williamsburg, Virginia. The basic features essential to a standard message passing interface were discussed, and a working group established to continue the standardization process. Preliminary draft proposal developed subsequently.
- Nov 1992: Working group meets in Minneapolis. MPI draft proposal (MPI1) from ORNL presented. Group adopts procedures and organization to form the MPI Forum. It eventually comprised of about 175 individuals from 40 organizations including parallel computer vendors, software writers, academia and application scientists.
- Nov 1993: Supercomputing 93 conference - draft MPI standard presented.
- May 1994: Final version of MPI-1.0 released
	- MPI-1.1 (Jun 1995)
	- MPI-1.2 (Jul 1997)
	- MPI-1.3 (May 2008).
- 1998: MPI-2 picked up where the first MPI specification left off, and addressed topics which went far beyond the MPI-1 specification.
	- MPI-2.1 (Sep 2008)
	- MPI-2.2 (Sep 2009)
- Sep 2012: The MPI-3.0 standard was approved.
	- MPI-3.1 (Jun 2015)
- Current: The MPI-4.0 standard is under development.

# About the execution environment

In this book is used a Docker container that enables to execute in browser MPI program. 
The Docker container is available on public repository on [GitHub](https://github.com/spagnuolocarmine/docker-mpi). The execution environment provides an Ubuntu 18.04 linux machine and several softwares. The execution environments provide the last version of [OpenMPI](https://www.open-mpi.org/), the MPI implementation used in this book. 

You can build your local docker to experiment on your local machine varying the number of MPI processes, by pull from the official Docker registry the image:  docker pull ```spagnuolocarmine/docker-mpi:latest```. Or you can build the docker image by yourself:

```
git clone https://github.com/spagnuolocarmine/docker-mpi.git
cd docker-mpi
docker build --no-cache -t dockermpi .
docker run -it -t dockermpi:latest
```

# References

1. Peter Pacheco. 2011. An Introduction to Parallel Programming (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
2. Kai Hwang, Jack Dongarra, and Geoffrey C. Fox. 2011. Distributed and Cloud Computing: From Parallel Processing to the Internet of Things (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
3. Czech, Z. (2017). Introduction to Parallel Computing. Cambridge: Cambridge University Press.
4. Blaise Barney, Lawrence Livermore National Laboratory, Message Passing Interface (MPI) -- https://computing.llnl.gov/tutorials/mpi/#What
5. MPI: A Message-Passing Interface Standard -- https://www.mpi-forum.org/docs/mpi-2.2/mpi22-report.pdf
6. Wilson Greg, Kristian Hermansen. 2011. The Architecture of Open Source Applications, Volume II.
7. https://www.rookiehpc.com/mpi/docs/index.php
8. Beginning MPI (An Introduction in C)

# About the Author

Carmine Spagnuolo got his Master Degree cum laude in Computer Science at the Università degli Studi di Salerno in 2013. In January 2014, he started the Ph.D. program in Computer Science under the supervision of Professor Vittorio Scarano and has completed it in 2017. He is interested in Parallel Algorithms, Distributed Systems, Graph Theory, Social Networks and Agent-Based Simulations. Since 2010, he is involved in D-Mason research project, which is a distributed version of the MASON toolkit for Agent-Based simulations. He has worked on the architecture, visualization and communication strategies. In 2012 he got a grant from the Office of Naval Research (ONR) for visiting the George Mason University (GMU). In May 2017 and from October to December 2017, he visited the University of Chicago and Argonne National Laboratory, under the supervision of dott. Jonathan Ozik and exploiting a grant from ANL. Currently, he is a postdoc Researcher at the ISISLab laboratory of the University of Salerno. He is co-author of some papers in international refereed journals and conferences.

[spagnuolocarmine At gmail.com](mailto:spagnuolocarmine@gmail.com)