# Running on a local Docker environment

If you are looking for a simple environment to execute your MPI examples. The Docker platform is the best solution suits you.

> Docker is a set of platform as a service (PaaS) products that uses OS-level virtualization to deliver software in packages called containers. Containers are isolated from one another and bundle their own software, libraries and configuration files; they can communicate with each other through well-defined channels. All containers are run by a single operating-system kernel and are thus more lightweight than virtual machines. [Wikipedia](https://en.wikipedia.org/wiki/Docker_(software))

- 🐳 [Docker Ubuntu OpenMPI](https://hub.docker.com/r/spagnuolocarmine/docker-mpi)
- 🆘 Usage of book Docker environment: 
    - ```docker run -it --mount src="$(pwd)",target=/home,type=bind spagnuolocarmine/docker-mpi:latest```, executes the docker container, which mounts the current path in the ```/home``` folder of the container. 
    - However, in order to run the container (using the user root), you need to allow the execution of the ```mpirun``` command using the root user by adding the ```--allow-run-as-root``` option, for instance ```mpirun --allow-run-as-root -np 3 myprogram.out```.