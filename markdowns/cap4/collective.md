# Collective Communications Routines

Collective communication is defined as communication that involves a group or groups of processes. One of the key arguments in a call to a collective routine is a communicator that defines the group or groups of participating processes and provides a context for the operation. All processes in the group identified by the intracommunicator must call the collective routine.

The syntax and semantics of the collective operations are defined to be consistent with the syntax and semantics of the point-to-point operations. Thus, general datatypes are allowed and must match between sending and receiving processes. Several collective routines such as broadcast and gather have a single originating or receiving process. Such a process is called the root. Some arguments in the collective functions are specified as **significant only at root**, and are ignored for all participants except the root. 

To understand how collective operations apply to intercommunicators, is possible to view the MPI intracommunicator collective operations as fitting one of the following categories :
- All-To-One, such as gathering (see Figure) or reducing (see Figure)  in one process data.
- One-To-All, such as broadcasting (see Figure)  data on all processors in a group.
- All-To-All, such as executing one collective operation using all processors in a group as root.
- Other

![MPI_COLLECTIVE](/img/coll-fig1-22.gif

In the following, all the MPI collective communications will be described by example.

A fundamental collective communication is an explicit synchronization between processors in the group.

**MPI_BARRIER(comm)** If comm is an intracommunicator, MPI_BARRIER blocks the caller until all group members have called it. The call returns at any process only after all group members have entered the call.
```c
int MPI_Barrier(MPI_Comm comm)
```
- IN comm, communicator (handle)
