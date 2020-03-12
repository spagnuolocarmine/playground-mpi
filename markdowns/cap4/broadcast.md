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

