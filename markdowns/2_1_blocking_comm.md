# Point-to-Point Communication

As described, in the introduction an MPI process communicates using MPI communication operations. This Chapter describes the point-to-point  communication routines, their communications modes, and the blocking and non-blocking communications.  

MPI procedures  are  specified  using  a  language-independent  notation.   The  arguments  ofprocedure calls are marked as **IN**, **OUT**, or **INOUT**. The meanings of these are:
- IN:  the  call  may  use  the  input  value  but  does  not  update  the  argument  from  the perspective of the caller at any time during the call’s execution;
- OUT: the call may update the argument but does not use its input value;
- INOUT: the call may both use and update the argument.

There  is  one  special  case  —  if  an  argument  is  a  handle  to  an  opaque  object, and the object is updated by the procedure call, then the argument is marked INOUT or OUT. It is marked this way even though the handle itself is  not  modified  —  is used INOUT or OUT attribute  to  denote  that  what  the  handle references is updated.

## Blocking Send and Receive Operations

# Blocking Send

```c
MPI_SEND(buf, count, datatype, dest, tag, comm)
```
- IN buf, initial address of send buffer (choice)
- IN count, number of elements in send buffer (non-negative integer)
- IN datatype, datatype of each send buffer element (handle)
- IN dest rank of destination (integer)
- IN tag, message tag (integer)
- IN comm, communicator (handle)

THE _MPI\_Send_ is blocking:  it does not return until the message data and envelope have been safely stored away so that the sender is free to modify thesend buffer.  The message might be copied directly into the matching receive buffer, or it might be copied into a temporary system buffer. Message buffering decouples the send and receive operations.  A blocking send can complete as soon as the message was buffered, even if no matching receive has been executed bythe receiver.  On the other hand, message buffering can be expensive, as it entails additional memory-to-memory copying, and it requires the allocation of memory for buffering. 

### How do distinguish messages?

In addition to the data part, messages carry information that can be used to distinguish messages and selectively receive them.  This information consists of a fixed number of fields, which we collectively call the message envelope.  These fields are:

- source
- destination
- tag
- communicator

The message source is implicitly determined by the identity of the message sender.  The other fields are specified by arguments in the send operation. The message destination is specified by the _dest_ argument. The integer-valued message _tag_ is specified by the tag argument. This integer can beused  by  the  program  to  distinguish  different  types  of  messages. The  range  of  valid  tagvalues is 0,...,UB, where the value of UB is implementation dependent. In OpenMPI this values is defined by **MPI_TAG_UB**.


The _comm_ argument specifies the communicator that is used for the send operation.

### Remarks about communicators

A communicator specifies the communication context for a communication operation. Each communication context provides a separate “communication universe”:  messages are always received within the context they were sent, and messages sent in different contexts do not interfere. The  communicator  also  specifies  the  set  of  processes  that  share  this  communication context.  This process group is ordered and processes are identified by their rank within this group.  A  predefined  communicator **MPI_COMM_WORLD** is  provided  by MPI.  It  allows  communication with all processes that are accessible after MPI initialization and processes are identified by their rank in the group of _MPI\_COMM\_WORLD_.

# Blocking Receive

```c
MPI_RECV (buf, count, datatype, source, tag, comm, status)
```
- OUT buf, initial address of receive buffer (choice)
- IN count, number of elements in receive buffer (non-negative integer)
- IN datatype, datatype of each receive buffer element (handle)
- IN source rank of source or _MPI\_ANY\_SOURCE (integer) 
- IN tag, message tag or _MPI\_ANY\_TAG_ (integer)
- IN comm, communicator (handle)
- OUT status, status object (Status)

The receive buffer consists of the storage containing _count_ **consecutive** elements of the type specified by datatype, starting at addressbuf.  The length of the received message must be  less  than  or  equal  to  the  length  of  the  receive  buffer.   An  **overflow**  error  occurs  if  all incoming data does not fit, without truncation, into the receive buffer. If a message that is shorter than the receive buffer arrives, then only those locations corresponding to the (shorter) message are modified.

The  selection  of  a  message  by  a  receive  operation  is  governed  by  the  value  of  the message envelope.  A message can be received by a receive operation if its envelope matches the source, tag and comm values  specified  by  the  receive  operation. The  receiver  may specify  a  wildcard _MPI\_ANY\_SOURCE_ value  for source,  and/or  a  wildcard _MPI\_ANY\_TAG_ value  for tag,  indicating  that  any  source  and/or  tag  are  acceptable.   It  cannot  specify  awildcard  value  for _comm_. 

### Notice

Note the asymmetry between send and receive operations:  A receive operation may accept messages from an arbitrary sender, on the other hand, a send operation must specify a unique receiver.  This matches a “push” communication mechanism, where data transfer is effected by the sender (rather than a “pull” mechanism, where data transfer is effectedby the receiver). Source = destination is allowed, that is, a process can send a message to itself, however, it is unsafe to do so with the blocking send and receive operations, since this may lead to **deadlock**. 


## Sending and 

@[one]({"stubs": ["2/1.c"], "command": "/bin/bash /project/target/2/1.sh"})
