# Collective Communications Routines

Collective communication is defined as communication that involves a group or groups of processes. One of the key arguments in a call to a collective routine is a communicator that defines the group or groups of participating processes and provides a context for the operation. All processes in the group identified by the intracommunicator must call the collective routine.

The syntax and semantics of the collective operations are defined to be consistent with the syntax and semantics of the point-to-point operations. Thus, general datatypes are allowed and must match between sending and receiving processes. Several collective routines such as broadcast and gather have a single originating or receiving process. Such a process is called the root. Some arguments in the collective functions are specified as **significant only at root**, and are ignored for all participants except the root. 

To understand how collective operations apply to intercommunicators, is possible to view the MPI intracommunicator collective operations as fitting one of the following categories :
- All-To-One, such as gathering (see Figure) or reducing (see Figure)  in one process data.
- One-To-All, such as broadcasting (see Figure)  data on all processors in a group.
- All-To-All, such as executing one collective operation using all processors in a group as root.
- Other

![MPI_COLLECTIVE](/img/coll-fig1-22.gif)

In the following, all the MPI collective communications will be described by example.

A fundamental collective operation is the explicit synchronization between processors in a group.

**MPI_BARRIER(comm)** If comm is an intracommunicator, MPI_BARRIER blocks the caller until all group members have called it. The call returns at any process only after all group members have entered the call.

![MPI_BARRIER](/img/barrier.png)

```c
int MPI_Barrier(MPI_Comm comm)
```
- IN comm, communicator (handle)


@[MPI BARRIER]({"stubs": ["4/barrier.c"], "command": "/bin/bash /project/target/4/barrier.sh"})

# Broadcast

**MPI_BCAST(buffer, count, datatype, root, comm)** If comm is an intracommunicator, MPI_BCAST broadcasts a message from the process with rank root to all processes of the group, itself included. It is called by all members of the group using the same arguments for comm and root. On return, the content of root's buffer is copied to all other processes.

![MPI_BCAST](/img/MPI_BCAST.png)

```c
int MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int root,MPI_Comm comm)
```
- INOUT buffer, starting address of buffer (choice)
- IN count, number of entries in buffer (non-negative integer)
- IN datatype, data type of buffer (handle)
- IN root, rank of broadcast root (integer)
- IN comm, communicator (handle)

@[MPI BCAST]({"stubs": ["4/bcast.c"], "command": "/bin/bash /project/target/4/bcast.sh"})

## Why we should use collective operation for group communications?

MPI collective operations exploit optimized solutions to realize communication between processors in a group. For instance, the broadcasting operation exploits a tree structure  (as depicted in the Figure), which allows parallelizing the communications. 


![MPI_BCAST TREE](/img/broadcast_tree.png)


Obviously the effect of this optimization scales according to the number of processors involved in the communications. The following example presents a comparison between the MPI_BCAST operation and its version developed using MPI_Send and MPI_Receive. If you can not see the advantage to use the broadcast operation please run this experiment on more processors.

@[MPI BCAST COMPARE]({"stubs": ["4/compare_bcast.c"], "command": "/bin/bash /project/target/4/compare_bcast.sh"})

# Gather

**MPI_GATHER(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm)** If comm is an intracommunicator, each process (root process included) sends the contents of its send buffer to the root process. The root process receives the messages and stores them in rank order. General, derived datatypes are allowed for both sendtype and recvtype. The type signature of sendcount, sendtype on each process must be equal to the type signature of recvcount, recvtype at the root. This implies that the amount of data sent must be equal to the amount of data received, pairwise between each process and the root. Distinct type maps between sender and receiver are still allowed.

All arguments to the function are significant on process root, while on other processes, only arguments sendbuf, sendcount, sendtype, root, and comm are significant. The arguments root and comm must have identical values on all processes. Note that the recvcount argument at the root indicates the number of items it receives from each process, not the total number of items it receives.

![MPI_GATHER](/img/gather.png)

```c
int MPI_Gather(const void* sendbuf, int sendcount, MPI_Datatype sendtype,void* recvbuf, int recvcount, MPI_Datatype recvtype, int root,MPI_Comm comm)
```
- IN sendbuf,	starting address of send buffer (choice)
- IN sendcount,	number of elements in send buffer (non-negative integer)
- IN sendtype,	data type of send buffer elements (handle)
- OUT recvbuf,	address of receive buffer (choice, significant only at root)
- IN recvcount,	number of elements for any single receive (non-negative integer, significant only at root)
- IN recvtype,	data type of recv buffer elements (significant only at root) (handle)
- IN root,	rank of receiving process (integer)
- IN comm,	communicator (handle)

@[MPI GATHER]({"stubs": ["4/gather.c"], "command": "/bin/bash /project/target/4/gather.sh"})


**MPI_GATHERV(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm)** extends the functionality of MPI_GATHER by allowing a varying count of data from each process, since recvcounts is now an array. It also allows more flexibility as to where the data is placed on the root, by providing the new argument, displs. The data received from process j is placed into recvbuf of the root process beginning at offset displs[j] elements (in terms of the recvtype). The receive buffer is ignored for all non-root processes.

![MPI_GATHER_V](/img/gatherv.gif)

```c
int MPI_Gatherv(const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
```
- IN sendbuf,	starting address of send buffer (choice)
- IN sendcount,	number of elements in send buffer (non-negative integer)
- IN sendtype,	data type of send buffer elements (handle)
- OUT recvbuf,	address of receive buffer (choice, significant only at root)
- IN recvcounts,	non-negative integer array (of length group size) containing the number of elements that are received from each process (significant only at root)
- IN displs,	integer array (of length group size). Entry i specifies the displacement relative to recvbuf at which to place the - incoming data from process i (significant only at root)
- IN recvtype,	data type of recv buffer elements (significant only at root) (handle)
- IN root,	rank of receiving process (integer)
- IN comm,	communicator (handle)

@[MPI GATHER]({"stubs": ["4/gather_v.c"], "command": "/bin/bash /project/target/4/gather_v.sh"})



# Scatter

**MPI_SCATTER(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm)** takes an array of elements and distributes the elements in the order of process rank. An alternative description is that the root sends a message with MPI_Send(sendbuf, sendcount x n, sendtype, ...). This message is split into n equal segments, the i-th segment is sent to the i-th process in the group, and each process receives this message. The send buffer is ignored for all non-root processes.

![MPI_SCATTER](/img/scatter.png)

```c
int MPI_Scatter(const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
```
- IN sendbuf,	address of send buffer (choice, significant only at root)
- IN sendcount,	number of elements sent to each process (non-negative integer, significant only at root)
- IN sendtype,	data type of send buffer elements (significant only at root) (handle)
- OUT recvbuf,	address of receive buffer (choice)
- IN recvcount,	number of elements in receive buffer (non-negative integer)
- IN recvtype,	data type of receive buffer elements (handle)
- IN root,	rank of sending process (integer)
- IN comm,	communicator (handle)

@[MPI SCATTER]({"stubs": ["4/scatter.c"], "command": "/bin/bash /project/target/4/scatter.sh"})

**MPI_SCATTERV(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm)** is the inverse operation to MPI_GATHERV. MPI_SCATTERV extends the functionality of MPI_SCATTER by allowing a varying count of data to be sent to each process, since sendcounts is now an array. It also allows more flexibility as to where the data is taken from on the root, by providing an additional argument, displs.


```c
int MPI_Scatterv(const void* sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
```
- IN sendbuf,	address of send buffer (choice, significant only at root)
- IN sendcounts,	non-negative integer array (of length group size) specifying the number of elements to send to each rank
- IN displs	integer array (of length group size). Entry i specifies the displacement (relative to sendbuf) from which to take the outgoing data to process i
- IN sendtype	data type of send buffer elements (handle)
- OUT recvbuf	address of receive buffer (choice)
- IN recvcount	number of elements in receive buffer (non-negative integer)
- IN recvtype	data type of receive buffer elements (handle)
- IN root	rank of sending process (integer)
- IN comm	communicator (handle)

@[MPI SCATTERV]({"stubs": ["4/scatter_v.c"], "command": "/bin/bash /project/target/4/scatter_v.sh"})

# Other collective operations

- MPI_ALLGATHER, MPI_ALLGATHERV: A variation on Gather where all members of a group receive the result.
- MPI_ALLTOALL, MPI_ALLTOALLV: Scatter/Gather data from all members to all members of a group (also called complete exchange).
- MPI_ALLREDUCE, MPI_REDUCE: Global reduction operations such as sum, max, min, or user-defined functions, where the result is returned to all members of a group and a variation where the result is returned to only one member.

# Nonblocking Collective Communication

As described in Nonblocking Communication, performance of many applications can be improved by overlapping communication and computation, and many systems enable this. Nonblocking collective operations combine the potential benefits of nonblocking point-to-point operations, to exploit overlap and to avoid synchronization, with the optimized implementation and message scheduling provided by collective operations. One way of doing this would be to perform a blocking collective operation in a separate thread. An alternative mechanism that often leads to better performance (e.g., avoids context switching, scheduler overheads, and thread management) is to use nonblocking collective communication.

The nonblocking collective communication model is similar to the model used for nonblocking point-to-point communication. A nonblocking call initiates a collective operation, which must be completed in a separate completion call. Once initiated, the operation may progress independently of any computation or other communication at participating processes. In this manner, nonblocking collective operations can mitigate possible synchronizing effects of collective operations by running them in the "background". In addition to enabling communication-computation overlap, nonblocking collective operations can perform collective operations on overlapping communicators, which would lead to deadlocks with blocking operations. Their semantic advantages can also be useful in combination with point-to-point communication.

As in the nonblocking point-to-point case, all calls are local and return immediately, irrespective of the status of other processes. The call initiates the operation, which indicates that the system may start to copy data out of the send buffer and into the receive buffer. Once initiated, all associated send buffers and buffers associated with input arguments (such as arrays of counts, displacements, or datatypes in the vector versions of the collectives) should not be modified, and all associated receive buffers should not be accessed, until the collective operation completes. The call returns a request handle, which must be passed to a completion call.

All completion calls (e.g., MPI_WAIT) are supported for nonblocking collective operations. Similarly to the blocking case, nonblocking collective operations are considered to be complete when the local part of the operation is finished, i.e., for the caller, the semantics of the operation are guaranteed and all buffers can be safely accessed and modified. Completion does not indicate that other processes have completed or even started the operation (unless otherwise implied by the description of the operation). Completion of a particular nonblocking collective operation also does not indicate completion of any other posted nonblocking collective (or send-receive) operations, whether they are posted before or after the completed operation.


