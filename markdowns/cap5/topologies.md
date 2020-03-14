# Topologies

MPI topology mechanism is an extra, optional attribute that one can give to an intra-communicator; topologies cannot be added to inter-communicators. A topology can provide a convenient naming mechanism for the processes of a group (within a communicator), and additionally, _may assist the runtime system in mapping the processes onto hardware_.

As stated for Groups, Communicators, a process group in MPI is a collection of n processes. Each process in the group is assigned a rank between 0 and n-1. In many parallel applications a linear ranking of processes does not adequately reflect the logical communication pattern of the processes (which is usually determined by the underlying problem geometry and the numerical algorithm used). 

Often the processes are arranged in topological patterns such as two- or three-dimensional grids. More generally, the logical process arrangement is described by a graph. In this chapter we will refer to this logical process arrangement as the **virtual topology**.

A clear distinction must be made between the virtual process topology and the topology of the underlying, physical hardware. The virtual topology can be exploited by the system in the assignment of processes to physical processors, if this helps to improve the communication performance on a given machine. How this mapping is done, however, is outside the scope of MPI. The description of the virtual topology, on the other hand, depends only on the application, and is machine-independent. The functions that are described in this chapter deal with machine-independent mapping and communication on virtual process topologies.

## What are a virtual topologies?

The communication pattern of a set of processes can be represented by a graph. The nodes represent processes, and the edges connect processes that communicate with each other. MPI provides message-passing between any pair of processes in a group. There is no requirement for opening a channel explicitly. Therefore, a _missing link_ in the user-defined process graph does not prevent the corresponding processes from exchanging messages. It means rather that this connection is neglected in the virtual topology. This strategy implies that the topology gives no convenient way of naming this pathway of communication. Another possible consequence is that an automatic mapping tool (if one exists for the runtime environment) will not take account of this edge when mapping.

Specifying the virtual topology in terms of a graph is sufficient for all applications. However, in many applications the graph structure is regular, and the detailed set-up of the graph would be inconvenient for the user and might be less efficient at run time. A large fraction of all parallel applications use process topologies like _rings, two- or higher-dimensional grids, or tori_. These structures are completely defined by the number of dimensions and the numbers of processes in each coordinate direction. Also, the mapping of grids and tori is generally an easier problem than that of general graphs. Thus, it is desirable to address these cases explicitly.

### Example Cartesian Topology

Process coordinates in a Cartesian structure begin their numbering at 0. Row-major numbering is always used for the processes in a Cartesian structure. This means that, for example, the relation between group rank and coordinates for four processes in a (2 × 2) grid is as follows.

- coord (0,0):	rank 0
- coord (0,1):	rank 1
- coord (1,0):	rank 2
- coord (1,1):	rank 3

## Topologies Constructor

In the following several MPI topologies are described. The available MPI topologies are: **MPI_GRAPH** the graph topology, **MPI_CART** the cartesian topology, and **MPI_DIST_GRAPH** distributed graph topology. When is not defined a topology for a communicator the value **MPI_UNDEFINED** is used.

Moreover, MPI provides usefull function to inquiry topology, here the most important:
- **MPI_TOPO_TEST** returns the  type  of  topology  that  is  assigned  to  a communicator.
    ```c
    int MPI_Topo_test(MPI_Comm comm, int *status)
    ```
    - IN comm, communicator (handle)
    - OUT status, topology type of communicator comm (state)
- **MPI_GRAPH_GET** retrieve the graph-topologyinformation that was associated with a communicator.
    ```c
    int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[],int edges[])
    ```
    - IN comm, communicator with graph structure (handle)
    - IN maxindex, length of vector index in the calling program (integer)
    - IN maxedges, length of vector edges in the calling program (integer)
    - OUT index, array of integers containing the graph structure (for details see the definition of MPI_GRAPH_CREATE)
    - OUT edges, array of integers containing the graph structure
- **MPI_CART_GET** return the Cartesian topology information that was associated with a communicator.
    ```c
    int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[])
    ```
    - IN comm, communicator with Cartesian structure (handle)
    - IN maxdims, length of vectors dims, periods, and coords in the calling program (integer)
    - OUT dims, number of processes for each Cartesian dimension (array of integer)
    - OUT periods, periodicity ( true/ false) for each Cartesian dimension (array of logical)
    - OUT coords, coordinates of calling process in Cartesian structure (array of integer)
- **MPI_CART_RANK** translates the logical process coordinates to process ranks as they are used by the point-to-point routines.
    ```c
    int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank)
    ```
    - IN comm, communicator with Cartesian structure (handle)
    - IN coords, integer array (of size ndims) specifying the Cartesian coordinates of a process
    - OUT rank, rank of specified process (integer)
- **MPI_CART_COORDS** provides rank-to-coordinates translation (inverse mapping),
    ```c
    int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[])
    ```
    - IN comm, communicator with Cartesian structure (handle)
    - IN rank, rank of a process within group of comm (integer)
    - IN maxdims, length of vector coords in the calling program (integer)
    - OUT coords, integer array (of size ndims) containing the Cartesian coordinates of specified process (array of integers)


### Cartesian Constructor


**MPI_CART_CREATE**  returns a handle to a new communicator to which the Cartesian topology information is attached. If reorder is false then the rank of each process in the new group is identical to its rank in the old group. Otherwise, the function may reorder the processes (possibly so as to choose a good embedding of the virtual topology onto the physical machine). If the total size of the Cartesian grid is smaller than the size of the group of comm_old, then some processes are returned MPI_COMM_NULL, in analogy to MPI_COMM_SPLIT. If ndims is zero then a zero-dimensional Cartesian topology is created. The call is erroneous if it specifies a grid that is larger than the group size or if ndims is negative.


![Cartesian](/img/cartesian.png)

```c
int MPI_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart)
```
- IN comm_old,	input communicator (handle)
- IN ndims,	number of dimensions of Cartesian grid (integer)
- IN dims,	integer array of size ndims specifying the number of processes in each dimension
- IN periods,	logical array of size ndims specifying whether the grid is periodic ( true) or not ( false) in each dimension
- IN reorder,	ranking may be reordered ( true) or not ( false) (logical)
- OUT comm_cart, communicator with new Cartesian topology (handle)


@[MPI_Cart_create]({"stubs": ["5/cart.c"], "command": "/bin/bash /project/target/5/cart.sh"})

