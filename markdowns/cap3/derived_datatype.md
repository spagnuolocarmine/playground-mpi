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

### Contiguous
The simplest datatype constructor is MPI\_TYPE\_CONTIGUOUS which allows replication of a datatype into contiguous locations.

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

### Vector
The function MPI\_TYPE\_VECTOR is a more general constructor that allows replication  of  a  datatype  into  locations  that  consist  of  equally  spaced  blocks.   Each  block  is obtained  by  concatenating  the  same  number  of  copies  of  the  old  datatype.   The  spacing between blocks is a multiple of the extent of the old datatype.


![MPI_TYPE_VECTOR](/img/data-vector.jpeg)

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

A call to MPI\_TYPE\_CONTIGUOUS(count, oldtype, newtype) is equivalent to a call to MPI\_TYPE\_VECTOR(count, 1, 1, oldtype, newtype), or to a call to MPI\_TYPE\_VECTOR(1,count, n, oldtype, newtype), _n_ arbitrary.

@[MPI_Type_vector]({"stubs": ["3/mpi_vector.c"], "command": "/bin/bash /project/target/3/mpi_vector.sh"})

### Indexed
The function MPI\_TYPE\_INDEXED allows replication of an old datatype into a sequence of blocks (each block is a concatenation of the old datatype), where each blockcan  contain  a  different  number  of  copies  and  have  a  different  displacement.   All  block displacements are multiples of the old type extent.


![MPI_TYPE_INDEXED](/img/data-indexed.jpeg)

```c
MPI_TYPE_INDEXED(count, array_of_blocklengths, array_of_displacements, oldtype,newtype)
```
- IN count, number of blocks — also number of entries inarray_of_displacements and array_of_blocklengths(non-negative integer)
- IN array_of_blocklengths, number of elements per block (array of non-negative integers)
- IN array_of_displacements, displacement  for  each  block,  in  multiples  of oldtype extent (array of integer)
- IN oldtype, old datatype (handle)
- OUT newtype, new datatype (handle)

#### C version
```c
int MPI_Type_indexed(int count, const int array_of_blocklengths[],const int array_of_displacements[], MPI_Datatype oldtype,MPI_Datatype *newtype)
```

@[MPI_Type_indexed]({"stubs": ["3/mpi_indexed.c"], "command": "/bin/bash /project/target/3/mpi_indexed.sh"})


### Struct
MPI\_TYPE\_CREATE\_STRUCT is  the  most  general  type  constructor. Allows the programmer to define a newdata type formed by completely defined map of the component data types.


![MPI_TYPE_STRCUT](/img/data-strcut.jpeg)

```c
MPI_TYPE_CREATE_STRUCT(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype)
```
- IN count, number of blocks (non-negative integer) — also number  of  entries  in  arrays array_of_types,array_of_displacement sandarray_of_blocklengths 
- IN array_of_blocklength, number of elements in each block (array of non-negative integer)
- IN array_of_displacements, byte displacement of each block (array of integer)
- IN array_of_types, type  of  elements  in  each  block  (array  of  handles  to datatype objects)
- OUT newtype, new datatype (handle)

#### C version
```c
int MPI_Type_create_struct(int count, const int array_of_blocklengths[],const MPI_Aint array_of_displacements[],const MPI_Datatype array_of_types[], MPI_Datatype *newtype
```

@[MPI_Type_struct]({"stubs": ["3/mpi_struct.c"], "command": "/bin/bash /project/target/3/mpi_struct.sh"})




