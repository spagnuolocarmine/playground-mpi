# Distributed-Memory Programming with MPI

Recall that the world of parallel multiple instruction, multiple data, or MIMD, com- puters is, for the most part, divided into distributed-memory and shared-memory systems. From a programmer’s point of view, a distributed-memory system consists of a collection of core-memory pairs connected by a network, and the memory associated with a core is directly accessible only to that core. On the other hand, from a programmer’s point of view, a shared-memory system consists of a col- lection of cores connected to a globally accessible memory, in which each core can have access to any memory location. 

![mpimodel](/img/mpimodel.png) 


Recall that in message-passing programs, a program running on one core-memory pair is usually called a process, and two processes can communicate by calling func- tions: one process calls a send function and the other calls a receive function. The implementation of message-passing that we’ll be using is called MPI, which is an abbreviation of Message-Passing Interface. MPI is not a new programming lan- guage. It defines a library of functions that can be called from C, C++, and Fortran programs. We’ll learn about some of MPI’s different send and receive functions. We’ll also learn about some “global” communication functions that can involve more than two processes. These functions are called collective communications. In the pro- cess of learning about all of these MPI functions, we’ll also learn about some of the


# References

1. Peter Pacheco. 2011. An Introduction to Parallel Programming (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
2. Kai Hwang, Jack Dongarra, and Geoffrey C. Fox. 2011. Distributed and Cloud Computing: From Parallel Processing to the Internet of Things (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
3. Czech, Z. (2017). Introduction to Parallel Computing. Cambridge: Cambridge University Press.

# About the Author

Carmine Spagnuolo got his Master Degree cum laude in Computer Science at the Università degli Studi di Salerno in 2013. In January 2014, he started the Ph.D. program in Computer Science under the supervision of Professor Vittorio Scarano and has completed it in 2017. He is interested in Parallel Algorithms, Distributed Systems, Graph Theory, Social Networks and Agent-Based Simulations. Since 2010, he is involved in D-Mason research project, which is a distributed version of the MASON toolkit for Agent-Based simulations. He has worked on the architecture, visualization and communication strategies. In 2012 he got a grant from the Office of Naval Research (ONR) for visiting the George Mason University (GMU). In May 2017 and from October to December 2017, he visited the University of Chicago and Argonne National Laboratory, under the supervision of dott. Jonathan Ozik and exploiting a grant from ANL. Currently, he is a postdoc Researcher at the ISISLab laboratory of the University of Salerno. He is co-author of some papers in international refereed journals and conferences.

[spagnuolocarmine At gmail.com](mailto:spagnuolocarmine@gmail.com)