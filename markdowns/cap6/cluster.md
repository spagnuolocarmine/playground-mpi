# How to create  an MPI cluster machine on Amazon AWS?

## Cluster Scenario 

- **1 Master Node**, where we develop and compile our program for all cluster node.
- **N Slaves**, where we run the MPI program to execute benchmarks. 

## Our computing environment Ubuntu with OpenMPI 

For running our experiment based on MPI and C language we use a Linux machine running the MPI implementation [OpenMPI](https://www.open-mpi.org/). The OpenMPI installation requires that all machines in the cluster have configured the same user and exchanged the SSH keys.

For this reason, the [repository](https://github.com/spagnuolocarmine) provides several installation scripts to build our computing environment on a Ubuntu Linux machine.

The script **install2020.sh** is able to install the following environment:
- user: pcpc
- applications: 
    - vim, an shell text editor.
    - htop, an interactive process viewer for Unix systems.
    - OpenMPI 4.0.
    - OpenMP included in the GNU GCC (last version).

Moreover, during the environment installation the script also exchanges the ssh key for the user pcpc.


## Example: configure a MPI cluster of two nodes?

Here is described how to execute and manually configure a cluster of two _t2.micro_ instances using the AWS WebConsole.

1. Create a new key-pair and store it on your local machine, suppose that the name of the key is _kcluster_.
2. Start two new t2.micro instances using the Ubuntu AMI (latest) and select the _kcluster_ key-pair, additionally rename it as _master_ and _slave0_. Set a new rule to the default security group that allows to open all TCP ports (0-65535) from anywhere (you can do it in the Configure Security Group tab).
3. Execute on the _master_ node the command ```ssh-keygen`` in order to generate new ssh key pairs for configure the access to the cluser. Note. By using this command without parameters the key is stored in the folder .ssh, in the file id_rsa e id_rsa.pub.
4.  Download and your local machine the [install.sh](https://github.com/spagnuolocarmine/ubuntu-openmpi-openmp/blob/master/install.sh) script and change the SSH key pairs using the previous generated key.
5. Copy the install.sh using SCP on all nodes ```scp -i kcluster install.sh ubuntu@ec2-34-207-88-239.compute-1.amazonaws.com:```.
6. Connect via SSH ```ssh -i kcluster_ubuntu@ec2-34-207-88-239.compute-1.amazonaws.com:``` and execute install.sh on all nodes.


