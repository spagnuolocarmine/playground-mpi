<img src="cover.png" alt="logo" height="120" align="right" href="http://bit.ly/have-fun-with-mpi"/>

# Have fun with MPI in C

*An interactive tutorial playground available on [Tech.io](http://bit.ly/have-fun-with-mpi).*

[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/) 
[![Open Source Love svg3](https://badges.frapsoft.com/os/v3/open-source.svg?v=103)](http://bit.ly/have-fun-with-mpi)


[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/spagnuolocarmine/playground-mpi) 
[![GitHub issues](https://img.shields.io/github/issues/Naereen/StrapDown.js.svg)](https://github.com/spagnuolocarmine/playground-mpi/issues/) 


[![Donate](https://img.shields.io/badge/PayPal-Donate%20to%20Author-blue.svg)](https://www.paypal.me/CarmineSpagnuolo) [![Ask Me Anything !](https://img.shields.io/badge/Ask%20me-anything-1abc9c.svg)](https://github.com/spagnuolocarmine/playground-mpi/issues)
[![Tweet](https://img.shields.io/twitter/url/http/shields.io.svg?style=social)](https://twitter.com/intent/tweet?text=Have%20fun%20with%20MPI%20in%20C%20&url=http://bit.ly/have-fun-with-mpi&hashtags=c,mpi,programming,tutorial,parallel-computing,distributed-computing,distributed-memory) 



# Book Execution Environment

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
7. MPI: A Message-Passing Interface Standard -- https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf
8. Wilson Greg, Kristian Hermansen. 2011. The Architecture of Open Source Applications, Volume II.
9. https://www.rookiehpc.com/mpi/docs/index.php
10. Beginning MPI (An Introduction in C)
11. Virtual Workshop Cornell -- https://cvw.cac.cornell.edu/MPIP2P
12. MPI by Blaise Barney, Lawrence Livermore National Laboratory -- https://computing.llnl.gov/tutorials/mpi/
13. https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/
14. https://mpi.deino.net
