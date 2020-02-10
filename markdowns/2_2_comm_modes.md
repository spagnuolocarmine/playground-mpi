# Communication Modes

The send call described is _blocking_:  it does not return until the message data and envelope have been safely stored away so that the sender is free to modify thesend buffer.  The message might be copied directly into the matching receive buffer, or it might be copied into a temporary system buffer. Message buffering decouples the send and receive operations.  A blocking send can complete as soon as the message was buffered, even if no matching receive has been executed bythe receiver.  On the other hand, message buffering can be expensive, as it entails additionalmemory-to-memory copying, and it requires the allocation of memory for buffering.

MPI offers the choice of several communication modes that allow one to control the choice of the communication protocol. The send call described uses the standard communication mode.  In this mode, it is up to MPI to decide whether outgoing messages will be buffered. MPI may buffer outgoing messages.  In such a case,  the send call may complete before a matching receive is invoked.  On the other hand, buffer space may be unavailable, or MPI may choose not to buffer outgoing messages, for performance reasons.  In this case, the send call will not complete until a matching receive has been posted, and the data has been moved to the receiver.

_Thus, a send in standard mode can be started whether or not a matching receive hasbeen posted.  It may complete before a matching receive is posted.  The standard mode send is non-local:  successful completion of the send operation may depend on the occurrence of a matching receive._

## Buffered Mode

A buffered mode send operation can be started whether or not a matching receivehas been posted.  It may complete before a matching receive is posted.  However, unlike the standard send, this operation islocal, and its completion does not depend on the occurrence of a matching receive.  Thus, if a send is executed and no matching receive is posted, then MPI must buffer the outgoing message, so as to allow the send call to complete. An error willoccur if there is insufficient buffer space.  The amount of available buffer space is controlled by the user.  Buffer allocation by the user may be required for the bufferedmode to be effective.

```c
MPI_BSEND (buf, count, datatype, dest, tag, comm)
```
- IN buf, initial address of send buffer (choice)
- IN count, number of elements in send buffer (non-negative integer)
- IN datatype, datatype of each send buffer element (handle)
- IN dest, rank of destination (integer)
- IN tag, message tag (integer)
- IN comm, communicator (handle)

# C version
```c
int MPI_Bsend(const void* buf, int count, MPI_Datatype datatype, int dest,int tag, MPI_Comm comm)
```

@[MPI_BSEND]({"stubs": ["2/2.c"], "command": "/bin/bash /project/target/2/2.sh"})


## Synchronous Mode

A send that uses thesynchronousmode can be started whether or not a matchingreceive was posted. However, the send will complete successfully only if a matching receive isposted, and the receive operation has started to receive the message sent by the synchronoussend.  Thus, the completion of a synchronous send not only indicates that the send buffercan  be  reused,  but  it  also  indicates  that  the  receiver  has  reached  a  certain  point  in  its execution,  namely that it has started executing the matching receive.  If both sends andreceives are blocking operations then the use of the synchronous mode provides synchronouscommunication semantics:  a communication does not complete at either end before bothprocesses rendezvous at the communication.  A send executed in this mode isnon-local.

```c
MPI_GET_COUNT(status, datatype, count)
```
- IN status, return status of receive operation (Status)
- IN datatype, datatype of each receive buffer entry (handle)
- OUT count, number of received entries (integer)

# C version
```c
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype,int *count)
```

## Ready Mode

A send that uses thereadycommunication mode may be startedonlyif the matchingreceive is already posted.  Otherwise, the operation is erroneous and its outcome is unde-fined.  On some systems, this allows the removal of a hand-shake operation that is otherwiserequired and results in improved performance.  The completion of the send operation doesnot depend on the status of a matching receive, and merely indicates that the send buffercan be reused.  A send operation that uses the ready mode has the same semantics as astandard  send  operation,  or  a  synchronous  send  operation;  it  is  merely  that  the  senderprovides additional information to the system (namely that a matching receive is alreadyposted), that can save some overhead.  In a correct program, therefore, a ready send couldbe replaced by a standard send with no effect on the behavior of the program other thanperformance.

```c
MPI_GET_COUNT(status, datatype, count)
```
- IN status, return status of receive operation (Status)
- IN datatype, datatype of each receive buffer entry (handle)
- OUT count, number of received entries (integer)

# C version
```c
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype,int *count)
```
