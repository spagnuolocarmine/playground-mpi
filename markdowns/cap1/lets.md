![cover](/img/cover.png)

> __Carmine Spagnuolo, Ph.D.__, Department of Computer Science, Università degli Studi di Salerno

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">
<img alt="Licenza Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" />
</a><br />This work is shared under the 
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.</a>

# Preface

Hi guys! Either you are a Computer Science student, or just a brave programmer who wants to start learning the basic of parallel programming in shared and/or distributed memory systems, this (play)book will light your way on (hopefully!).

First, why a playground on Tech.io? Generally, among others, a playground is a useful tool to explain both general concepts or more specific topics. What is amazing, however, it is the possibility to add runnable code samples that every reader can hack. Basically, you can play with snippets of code: just type a few lines and see what will change the next time you run that piece.

This playground is focused on Programming with MPI. Starting from what is (M)essage (P)assing (I)nterface, we will then approach and work with OpenMPI, an open-source MPI implementation. You will find a bunch of runnable snippets for each newly introduced concept, along with end-chapter questions. Nothing is mandatory, but you are strongly encouraged to try things out. The examples are in the C language, so knowing the Ritchie’ language is mandatory (we hope that you already know, if you have reached this book).

All we need to do now, it is just taking off. Seat back, relax, and code.

> __Alessia Antelmi__, PhD Student. Department of Computer Science, Università degli Studi di Salerno



# Book outline

1. Introduction. A brief introduction to distributed computing using distributed memory paradigm and MPI.
    - What is distributed computing?
    - Take the first steps, Hello world
    - The OpenMPI Architecture
    - MPI Programming
    - Chapter Questions
2. Point-to-Point communication. This chapter introduces synchronous and asynchronous communications of the MPI standard.
    - MPI Memory model
    - Blocking Communication
    - Communication Modes
    - Non-Blocking Communication
    - Chapter Questions
3. Datatypes. This chapter introduces Datatypes of the MPI standard.
    - Communicate noncontiguous data
    - Derived Datatypes
    - Chapter Questions
4. Collective communications. This chapter introduces the collective communications of the MPI standard.
    - Collective communications Overview
    - MPI Groups
    - MPI Communicators
    - Collective Communications Routines
    - Chapter Questions
5. Communication Topologies. A brief introduction to MPI topologies.
    - MPI Process Topologies
    - Chapter Questions
6. HPC for all, an MPI cluster on Amazon AWS. This chapter introduces how to create an MPI cluster machine on Amazon AWS. 
     - MPI Amazon AWS Cluster


## Changelogs

- 17/03/2020. This book is currently under development. Anyway yeah, you can start and I will finish in a few weeks (and we will provide a proofread).

# Introduction

## What is distributed computing? - Distributed-Memory Programming with MPI

Recall that the world of parallel multiple instruction, multiple data, or MIMD, computers are, for the most part, divided into distributed-memory and shared-memory systems. From a programmer’s point of view, a distributed-memory system consists of a collection of core-memory pairs connected by a network, and the memory associated with a core is directly accessible only to that core. On the other hand, from a programmer’s point of view, a shared-memory system consists of a collection of cores connected to globally accessible memory, in which each core can have access to any memory location. 

![mpimodel](/img/mpimodel.png) 


Recall that in message-passing programs, a program running on one core-memory pair is usually called a process, and two processes can communicate by calling functions: one process calls a send function and the other calls a receive function. The implementation of message-passing that we’ll be using is called MPI, which is an abbreviation of Message-Passing Interface. MPI is not a new programming language. It defines a library of functions that can be called from C, C++, and Fortran programs. We’ll learn about some of the MPI’s different send and receive functions. We’ll also learn about some “global” communication functions that can involve more than two processes. These functions are called collective communications. In the process of learning about all of these MPI functions, we’ll also learn about some of the fundamental issues involved in writing message-passing programs–issues such as data partitioning and I/O in distributed-memory systems. We’ll also revisit the issue of parallel program performance.

## What is MPI?

- M P I = Message Passing Interface
- MPI is a specification for the developers and users of message passing libraries. By itself, it is NOT a library - but rather the specification of what such a library should be.
- MPI primarily addresses the message-passing parallel programming model: data is moved from the address space of one process to that of another process through cooperative operations on each process.
- Simply stated, the goal of the Message Passing Interface is to provide a widely used standard for writing message-passing programs. The interface attempts to be:
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

### History and Evolution of MPI:

- MPI has resulted from the efforts of numerous individuals and groups that began in 1992. Some history:
- The 1980s - early 1990s: Distributed memory, parallel computing develops, as do a number of incompatible software tools for writing such programs - usually with tradeoffs between portability, performance, functionality, and price. Recognition of the need for a standard arose.
MPI Evolution
- Apr 1992: Workshop on Standards for Message Passing in a Distributed Memory Environment, sponsored by the Center for Research on Parallel Computing, Williamsburg, Virginia. The basic features essential to a standard message passing interface were discussed, and a working group established to continue the standardization process. A preliminary draft proposal developed subsequently.
- Nov 1992: Working group meets in Minneapolis. MPI draft proposal (MPI1) from ORNL presented. The group adopts procedures and organization to form the MPI Forum. It eventually comprised about 175 individuals from 40 organizations including parallel computer vendors, software writers, academia and application scientists.
- Nov 1993: Supercomputing 93 conference - draft MPI standard presented.
- May 1994: Final version of MPI-1.0 released
	- MPI-1.1 (Jun 1995)
	- MPI-1.2 (Jul 1997)
	- MPI-1.3 (May 2008).
- 1998: MPI-2 picked up where the first MPI specification left off and addressed topics that went far beyond the MPI-1 specification.
	- MPI-2.1 (Sep 2008)
	- MPI-2.2 (Sep 2009)
- Sep 2012: The MPI-3.0 standard was approved.
	- MPI-3.1 (Jun 2015)
- Current: The MPI-4.0 standard is under development.


# Book features and recommendations

- All arguments are discussed and experimented during the reading by using simple examples in C.
- By using this book you are able to learn in a more dynamic way.
- You can change the example and integrate it with your code to directly experiment with the topic that you have studied.
- Each example run with a fixed number of processors takes in mind this if you change the code.
- Do (and re-do) the chapter questions.

## Exercises Execution Environment

This book uses a Docker container that enables execution in the browser MPI program. 
The Docker container is available on a public repository on [GitHub](https://github.com/spagnuolocarmine/docker-mpi). The execution environment provides an Ubuntu 18.04 Linux machine and software. The execution environments provide the last version of [OpenMPI](https://www.open-mpi.org/), the MPI implementation used in this book. 

You can build your local docker to experiment on your local machine varying the number of MPI processes, by a pull from the official Docker registry the image:  docker pull ```spagnuolocarmine/docker-mpi:latest```. Or you can build the docker image by yourself:

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
7. MPI: A Message-Passing Interface Standard -- https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf
8. Wilson Greg, Kristian Hermansen. 2011. The Architecture of Open Source Applications, Volume II.
9. https://www.rookiehpc.com/mpi/docs/index.php
10. Beginning MPI (An Introduction in C)
11. Virtual Workshop Cornell -- https://cvw.cac.cornell.edu/MPIP2P
12. MPI by Blaise Barney, Lawrence Livermore National Laboratory -- https://computing.llnl.gov/tutorials/mpi/
13. https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/
14. https://mpi.deino.net

## Suggested readings

- Peter Pacheco. 2011. An Introduction to Parallel Programming (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
- Czech, Z. (2017). Introduction to Parallel Computing. Cambridge: Cambridge University Press.
- Maurice Herlihy and Nir Shavit. 2008. The Art of Multiprocessor Programming. Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
- Andy Oram, Greg Wilson, 2008, Beautiful Code, Leading Programmers Explain How They Think,  O'Reilly Media.
- [Idiomatic Expressions in C By Adam Petersen](https://www.adamtornhill.com/Idiomatic_expressions_in_C.pdf). 
- Mandel Cooper, Advanced Bash Scripting, 2010.

# About the Author

Carmine Spagnuolo got his Master's Degree cum laude in Computer Science at the Università degli Studi di Salerno in 2013. In January 2014, he started the Ph.D. program in Computer Science under the supervision of Professor Vittorio Scarano and has completed it in 2017.

He is interested in Parallel Algorithms, Distributed Systems, Graph Theory, Social Networks, and Agent-Based Simulations. Since 2010, he is involved in the D-MASON research project, which is a distributed version of the MASON toolkit for Agent-Based simulations. He has worked on architecture, visualization and communication strategies. 

In 2012 he got a grant from the Office of Naval Research (ONR) for visiting George Mason University (GMU). In May 2017 and from October to December 2017, he visited the University of Chicago and Argonne National Laboratory, under the supervision of Dott. Jonathan Ozik and exploiting a grant from ANL. In November 2019 he was a visiting researcher at  George Mason University (GMU) under supervising Prof. Sean Luke. Since 2018 he is involved in the Hypergraph research group formed by researches of Università degli Studi di Salerno, Università degli Studi della Campania "Luigi Vanvitelli", Warsaw School of Economics, and Ryerson University.

Currently, he is a Postdoc Researcher at the ISISLab laboratory of the Università degli Studi di Salerno. He is co-author of more than 20 papers in international refereed journals and conferences.

[spagnuolocarmine At gmail.com](mailto:spagnuolocarmine@gmail.com)