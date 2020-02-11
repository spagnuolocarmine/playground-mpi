# Derived Datatypes

MPI allows the programmer to create your own data types,  analogous to defining structures in C. MPI data types are mostly of use if you want to send multiple items in one message. Derived types allows to create new contiguous data type consisting of an array of elements of another data type;  a vector data type consisting of regularly spaced blocks of elements of a component type; not regularly spaced data, there is the indexed data type , where you specify an array of index locations for blocks of elements of a component type; and struct data type can accomodate multiple data types. 

A general datatype is an opaque object that specifies two things:
- A sequence of basic datatypes.
- A sequence of integer (byte) displacements.

The  displacements  are  not  required  to  be  positive,  distinct,  or  in  increasing  order.

### Process to create and use a new Datatype

1. Create your own datatype using Datatype Constructors
2. Commit your datatype 
3. Use it in your communications routines
4. Free your datatype

## Commit and Free your Datatype

Before to describe the construction of data type, we present how to commit and free a new data type, because these functions will be used in the examples.

A datatype object has to be _committed_ before it can be used in a communication.  As an argument in datatype constructors, _uncommitted_ and also committed datatypes can be used.  There is no need to commit basic datatypes (they are "pre-committed").

```c
MPI_TYPE_COMMIT(datatype)
```
- INOUT datatype, datatype that is committed (handle)

#### C version
```c
int MPI_Type_commit(MPI_Datatype *datatype)
```

A datatype that will be not be used again must be freed.

```c
MPI_TYPE_FREE(datatype)
```
- INOUT datatype, datatype that is freed (handle)

#### C version
```c
int MPI_Type_free(MPI_Datatype *datatype
```

## Datatype Constructors

**Contiguous** The simplest datatype constructor is MPI\_TYPE\_CONTIGUOUS which allows replication of a datatype into contiguous locations.

![MPI_TYPE_CONTIGUOUS](/img/data-contiguous.jpeg)
```c
MPI_TYPE_CONTIGUOUS(count, oldtype, newtype)
```
- IN count, replication count (non-negative integer)
- IN oldtype, old datatype (handle)
- OUT newtype, new datatype (handle)

#### C version
```c
int MPI_Type_contiguous(int count, MPI_Datatype oldtype,MPI_Datatype *newtype)
```

@[MPI_Type_contiguous]({"stubs": ["3/mpi_contiguous.c"], "command": "/bin/bash /project/target/3/mpi_contiguous.sh"})


**Vector** The function MPI\_TYPE\_VECTOR is a more general constructor that allows replication  of  a  datatype  into  locations  that  consist  of  equally  spaced  blocks.   Each  block  is obtained  by  concatenating  the  same  number  of  copies  of  the  old  datatype.   The  spacing between blocks is a multiple of the extent of the old datatype.
```c
MPI_TYPE_VECTOR(count, blocklength, stride, oldtype, newtype)
```
- IN count, number of blocks (non-negative integer)
- IN blocklength, number of elements in each block (non-negative integer)
- IN stride, number of elements between start of each block (integer)
- IN oldtype, old datatype (handle)
- OUT newtype, new datatype (handle)

#### C version
```c
int MPI_Type_vector(int count, int blocklength, int stride,MPI_Datatype oldtype, MPI_Datatype *newtype)
```








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
