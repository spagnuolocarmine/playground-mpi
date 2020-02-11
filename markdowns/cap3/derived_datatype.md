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

## Address and Size Functions useful for Datatype construction

The displacements in a general datatype are relative to some initial buffer address. Absolute addresses can be substituted for these displacements: we treat them as displacements relative to "address zero"  the start of the address space. This initial address zero is in-dicated by the constant MPI\_BOTTOM. 

The address of a location in memory can be found by invoking the function MPI\_GET\_ADDRESS, which uses the MPI\_Aint value, that is a signed  integer, or more in details a C type that holds any valid address.  Moreover, the relative  displacement between  two  absolute  addresses  can be  calculated  with  the  function MPI\_AINT\_DIFF.  A  new  absolute  address  as  sum  of  an absolute base address and a relative displacement can be calculated with the function MPI\_AINT\_ADD.  

```c
MPI_GET_ADDRESS(location, address)
```
- IN location, location in caller memory (choice)
- OUT address, address of location (integer)

#### C version
```c
int MPI_Get_address(const void *location, MPI_Aint *address)
```
The following auxiliary functions provide useful information on derived datatypes.

- Size of a datatype: return the number of bytes occupied by entries in the datatype.

```c
MPI_TYPE_SIZE(datatype, size)
```
- IN datatype, datatype (handle)
- OUT size, datatype size (integer)

#### C version
```c
int MPI_Type_size(MPI_Datatype datatype, int *size)
```
- Datatype extend, get the lower bound and extent for a Datatype.

```c
MPI_TYPE_GET_EXTENT(datatype, lb, extent)
```
- IN datatype, datatype to get information on (handle)
- OUT lblower bound of datatype (integer)
- OUT extent, extent of datatype (integer)

#### C version
```c
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb,MPI_Aint *extent)
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


![MPI_TYPE_STRCUT](/img/data-struct.jpeg)

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




