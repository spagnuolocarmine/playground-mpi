# The Message-Passing Model 

Each process has to send/receive data to/from other processes. For instance, consider the array of integers sorting the problem. Two processors divide the problem into two sub-problems, at the end the communicate and order the whole array.

![MPIINTSORTING](/img/sorting.png)

### MPI Simple communication model

![MPIINTSORTING](/img/sendreceive.png)

Data communication in MPI is like email exchange. One process sends a copy of the data to another process (or a group of processes), and the other process receives it. Communication  requires the following information:

-  Sender has to know:
	- Whom to send the data to (receiver’s process **rank**).
	- What **kind of data** to send (100 integers or 200 characters, etc).
	- A user-defined **tag** for the message (think of it as an email subject; allows the receiver to understand what type of data is being received).
- Receiver “might” have to know:
	- Who is sending the data, the **rank** of the process (if the receiver does not know; in this case sender rank will be **MPI_ANY_SOURCE**, meaning anyone can send).
	- What **kind of data** is being received (partial information is fine, for instance is possible to receive up to 1000 integers).
	- What the user-defined **tag** of the message is (OK if the receiver does
	not know; in this case tag will be **MPI_ANY_TAG**).

@[Send Receive]({"stubs": ["ptop/send_receive.c"], "command": "/bin/bash /project/target/ptop/run2.sh"})

# MPI Types and Constants
  
## MPI Naming Convention
 
## MPI Data Types

## MPI Constants

