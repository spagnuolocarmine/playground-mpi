# Derived Datatypes

All  point  to  point  communications  use  only  buffers  containing  a sequence  of  identical  basic  datatypes.   This  is  too  constraining  on  two  accounts.   One  often wants to pass messages that contain values with different datatypes (e.g., an integer count, followed by a sequence of real numbers); and one often wants to send noncontiguous data  (e.g.,  a  sub-block  of  a  matrix).  

One  solution  is  to  **pack  noncontiguous**  data  into a  contiguous  buffer  at  the  sender  site  and  unpack  it  at  the  receiver  site.  This  has  the disadvantage of requiring additional memory-to-memory copy operations at both sites.  However, MPI provides mechanisms to specify more general, mixed, and **noncontiguous communication buffers**.  It is up to the implementation to decide whether data should be first packed in a contiguous buffer before being transmitted, or whether it can be collected directly from where it resides.

## Sending noncontiguous data using Pack and Unpack

OpenMPI provides pack/unpack functions for sending noncontiguous data.  The user explicitly packs data into a contiguous buffer before sending it, and unpacks it from a contiguous buffer after receiving it. However, is convient using derivated type. We will introduce pack/unpack routines for compatibility with previous libraries or code.  

```c
MPI_PACK(inbuf, incount, datatype, outbuf, outsize, position, comm)
```
- IN inbuf, input buffer start (choice)
- IN incount, number of input data items (non-negative integer)
- IN datatype, datatype of each input data item (handle)
- OUT outbuf, output buffer start (choice)
- IN outsize, output buffer size, in bytes (non-negative integer)
- INOUT position, current position in buffer, in bytes (integer)
- IN comm, communicator for packed message (handle)

#### C version
```c
int MPI_Pack(const void* inbuf, int incount, MPI_Datatype datatype,void *outbuf, int outsize, int *position, MPI_Comm comm)
```

The  input  value  o fposition is  the  first  location  in  the  output  buffer  to  be  used  for packing. _position_ is incremented by the size of the packed message, and the output value of position is the first location in the output buffer following the locations occupied by the packed message.  The comm argument is the communicator that will be subsequently used for sending the packed message.

```c
MPI_UNPACK(inbuf, insize, position, outbuf, outcount, datatype, comm)
```
- IN inbuf, input buffer start (choice)
- IN insize, size of input buffer, in bytes (non-negative integer)
- INOUT position, current position in bytes (integer)
- OUT outbuf, output buffer start (choice)
- IN outcount, number of items to be unpacked (integer)
- IN datatype, datatype of each output data item (handle)
- IN comm, communicator for packed message (handle)

#### C version
```c
int MPI_Unpack(const void* inbuf, int insize, int *position, void *outbuf,int outcount, MPI_Datatype datatype, MPI_Comm comm)
```

Unpacks a message into the receive buffer specified by outbuf, outcount, datatype from the buffer space specified by inbuf and insize.  The output buffer can be any communication buffer allowed in MPI\_RECV. The input buffer is a contiguous storage area containing insize bytes, starting at address inbuf.  The input value of position is the first location in the input buffer occupied by the packed message. Position is incremented by the size of the packed message, so that the output value of position is the first location in the input buffer after the locations occupied by the message that was unpacked. Comm is the communicator usedto receive the packed message.

@[MPI_Pack and MPI_unpack]({"stubs": ["3/packunpack.c"], "command": "/bin/bash /project/target/3/packunpack.sh"})
