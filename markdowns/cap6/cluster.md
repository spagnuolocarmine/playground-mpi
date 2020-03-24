# How to create  an MPI cluster machine on Amazon AWS?

## Cluster Scenario 

- **1 Master Node**, where we develop and compile our program for all cluster node.
- **N Slaves**, where we run the MPI program to execute benchmarks. 

## Our computing environment Ubuntu with OpenMPI 

For running our experiment based on MPI and C language we use a Linux machine running the MPI implementation [OpenMPI](https://www.open-mpi.org/). The OpenMPI installation requires that all machines in the cluster have configured the same user and exchanged the SSH keys.

For this reason, the [repository](https://github.com/spagnuolocarmine/ubuntu-openmpi-openmp) provides installation scripts to build our computing environment on a Ubuntu Linux machine.

### Cluster Scenario

- 1 MASTER Node, here you have to generate the ssh-key and update the script.
- N SLAVEs, here you have to run the script using the keys generated on the master node.

### Installing

1. Copy on the MASTER node, from your local machine, the pem key: 
```scp -i "k.pem" k.pem ubuntu@ec2-34-239-142-46.compute-1.amazonaws.com:```
2. Login on the master node:
```ssh -i "k.pem" ubuntu@ec2-34-239-142-46.compute-1.amazonaws.com```
3. Clone the repository:
```git clone https://github.com/spagnuolocarmine/ubuntu-openmpi-openmp.git```
4. Generates the installing script for yourt cluster:
```source generateInstall.sh```, results in a ```install.sh``` script with new ssh-keys for the cluster.
5. The password for pcpc is root. If you like change use: ```sudo passwd pcpc```
6. For each SLAVE instance run the install script from the MASTER node:
```ssh -i <path-to-pem-file>  <connection-string-for-the-EC2-instace>  'bash -s' < install.sh```

## Environment
- user: pcpc pass: root
- applications: 
    - vim, an shell text editor.
    - htop, an interactive process viewer for Unix systems.
    - OpenMPI 4.0.
    - OpenMP included in the GNU GCC (last version).

Moreover, during the environment installation the script also exchanges the ssh key for the user pcpc.

# Running on a local Docker environment

If you are looking for a simple environment to execute your MPI examples. The Docker platform is the best solution suits you.

> Docker is a set of platform as a service (PaaS) products that uses OS-level virtualization to deliver software in packages called containers. Containers are isolated from one another and bundle their own software, libraries and configuration files; they can communicate with each other through well-defined channels. All containers are run by a single operating-system kernel and are thus more lightweight than virtual machines. [Wikipedia](https://en.wikipedia.org/wiki/Docker_(software))

- 🐳 [Docker Ubuntu OpenMPI](https://hub.docker.com/r/spagnuolocarmine/docker-mpi)
- 🆘 Usage of book Docker environment: 
    - ```docker run -it --mount src="$(pwd)",target=/home,type=bind spagnuolocarmine/docker-mpi:latest```, executes the docker container, which mounts the current path in the ```/home``` folder of the container. 
    - However, in order to run the container (using the user root), you need to allow the execution of the ```mpirun``` command using the root user by adding the ```--allow-run-as-root``` option, for instance ```mpirun --allow-run-as-root -np 3 myprogram.out```.