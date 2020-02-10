# Nonblocking Communication

One can improve performance on many systems by overlapping communication and computation.   This  is  especially  true  on  systems  where  communication  can  be  executed  autonomously by an intelligent communication controller.  Light-weight threads are one mechanism  for  achieving  such  overlap.   An  alternative  mechanism  that  often  leads  to  better performance is to use nonblocking communication.  

A **nonblockingsend** startcall initiates the send operation, but does not complete it.  The send start call can return before the message was copied out of the send buffer.  A separate send complete call is needed to complete the communication, i.e., to verify that the data has been copied out of the send buffer.  With suitable hardware, the transfer of data out of the sender memory may proceed concurrently with computations done at the sender after the send was initiated and before it completed. 

Similarly, a nonblocking receive start call initiates the receive operation, butdoes not complete it.  The call can return before a message is stored into the receive buffer. A separate receive complete call is needed to complete the receive operation and verify that the data has been received into the receive buffer.  With suitable hardware, the transfer of data into the receiver memory may proceed concurrently with computations done after the receive was initiated and before it completed.  The use of nonblocking receives may also avoid system buffering and memory-to-memory copying,  as information is provided early on the location of the receive buffer.

# Nonblocking Send and Receive Operations

Nonblocking send start calls can use the same four modes as blocking sends: standard, buffered, synchronous and ready.  These carry the same meaning.  Sends of all modes, ready excepted, can be started whether a matching receive has been posted or not; a nonblocking _ready_ send can be started only if a matching receive is posted.  In all cases, the send start call is local:  it returns immediately, irrespective of the status of other processes.  If the call causes  some  system  resource  to  be  exhausted,  then  it  will  fail  and  return  an  error  code. 

If the send mode is _synchronous_, then the send can complete only if a matching receive has started.  That is, a receive has been posted, and has been matched with the send.  In this case, the send-complete call is non-local.  Note that a synchronous, nonblocking send may complete, if matched by a nonblocking receive, before the receive complete call occurs. If the send mode is _buffered_ then the message must be buffered if there is no pending receive.  In this case, the send-complete call is local, and must succeed irrespective of the status of a matching receive.

If the send mode is _standard_ then the send-complete call may return before a matching receive is posted, if the message is buffered. Nonblocking sends can be matched with blocking receives, and vice-versa.

### Communication Request Objects

Nonblocking communications use opaque request objects to identify communication operations and match the operation that initiates the communication with the operation that terminates it.  These are system objects that are accessed via a handle.  A request object identifies various properties of a communication operation, such as the send mode, the communication buffer that is associated with it, its context, the tag and destination arguments to be used for a send, or the tag and source arguments to be used for a receive.  In addition, this object stores information about the status of the pending communication operation.

## Nonblocking Send and Receive

```c
MPI_ISEND(buf, count, datatype, dest, tag, comm, request)
```
- IN buf, initial address of send buffer (choice)
- IN count, number of elements in send buffer (non-negative integer)
- IN datatype, datatype of each send buffer element (handle)
- IN dest, rank of destination (integer)
- IN tag, message tag (integer)
- IN comm, communicator (handle)
- OUT request communication request (handle)

```c
MPI_IRECV (buf, count, datatype, source, tag, comm, request)
```
- OUT buf, initial address of receive buffer (choice)
- IN count, number of elements in receive buffer (non-negative integer)
- IN datatype, datatype of each receive buffer element (handle)
- IN source rank of source or _MPI\_ANY\_SOURCE (integer) 
- IN tag, message tag or _MPI\_ANY\_TAG_ (integer)
- IN comm, communicator (handle)
- OUT status, status object (Status)

#### C version
```c
int MPI_Irecv(void* buf, int count, MPI_Datatype datatype, int source,int tag, MPI_Comm comm, MPI_Request *request)
```

@[MPI_ISEND and MPI_Irecv]({"stubs": ["2/5.c"], "command": "/bin/bash /project/target/2/5.sh"})


## Nonblockiing Receive