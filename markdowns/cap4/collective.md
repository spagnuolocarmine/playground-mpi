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

## Broadcast


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

### Why we should use collective operation for group communications?

MPI collective operations exploit optimized solutions to realize communication between processors in a group. For instance, the broadcasting operation exploits a tree structure  (as depicted in the Figure), which allows parallelizing the communications. 


![MPI_BCAST TREE](/img/broadcast_tree.png)


Obviously the effect of this optimization scales according to the number of processors involved in the communications. The following example presents a comparison between the MPI_BCAST operation and its version developed using MPI_Send and MPI_Receive. If you can not see the advantage to use the broadcast operation please run this experiment on more processors.

@[MPI BCAST COMPARE]({"stubs": ["4/compare_bcast.c"], "command": "/bin/bash /project/target/4/compare_bcast.sh"})

