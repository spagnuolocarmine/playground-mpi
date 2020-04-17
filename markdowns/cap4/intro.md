# MPI Group and Communicator Management

A group is an ordered set of processes. Each process in a group is associated with a unique integer rank. Rank values start at zero and go to N-1, where N is the number of processes in the group. In MPI, a group is represented within system memory as an object. It is accessible to the programmer only by a "handle". A group is always associated with a communicator object.

A communicator encompasses a group of processes that may communicate with each other. All MPI messages must specify a communicator. In the simplest sense, the communicator is an extra "tag" that must be included with MPI calls. Like groups, communicators are represented within system memory as objects and are accessible to the programmer only by "handles". For example, the handle for the communicator that comprises all tasks is MPI\_COMM\_WORLD, and the MPI\_COMM\_NULL is the NULL communicator (some functions can return NULL).

Primary purposes of group and communicator objects:
- Allow you to organize tasks, based upon function, into task groups.
- Enable Collective Communications operations across a subset of related tasks.
- Provide basis for implementing user defined virtual topologies.
- Provide for safe communications.

![MPI_GROUP](/img/groups.gif)

<!-- ## Group Management

**MPI_GROUP_SIZE** returns  the size of a group.
```c
MPI_GROUP_SIZE(group, size)
```
- IN group, group (handle)
- OUT size, number of processes in the group (integer)

**C version**
```c
int MPI_Group_size(MPI_Group group, int *size)
```

**MPI_GROUP_RANK** returns the rank of this process in the given group.
```c
MPI_GROUP_RANK(group, rank)
```
- IN group, group (handle)
- OUT rank, rank of the calling process in group, or MPI\_UNDEFINED if the process is not a member (integer)

**C version**
```c
int MPI_Group_rank(MPI_Group group, int *rank)
```

**MPI_GROUP_TRANSLATE_RANKS** translates the ranks of processes in one group to those in another group.
```c
MPI_GROUP_TRANSLATE_RANKS(group1, n, ranks1, group2, ranks2)
```
- IN group1, group1 (handle)
- IN n, number of ranks in ranks1 and ranks2 arrays (integer)
- IN ranks1, array of zero or more valid ranks in group1 
- IN group2, group2 (handle)
- OUT ranks2, array  of  corresponding  ranks  in  group2, MPI\_UNDEFINED when no correspondence exists
**C version**
```c
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[],MPI_Group group2, int ranks2[])
```

**MPI_GROUP_COMPARE** compares two groups.
```c
MPI_GROUP_COMPARE(group1, group2, result)
```
- IN group1, first group (handle)
- IN group2, second group (handle)
- OUT result, result (integer)
**C version**
```c
int MPI_Group_compare(MPI_Group group1,MPI_Group group2, int *result)
```

### Group Constructors

Group  constructors  are  used  to  subset  and  superset  existing  groups.   These  constructors construct new groups from existing groups.  These are local operations, and distinct groups may  be  defined  on  different  processes;  a  process  may  also  define  a  group  that  does  notinclude  itself.   Consistent  definitions  are  required  when  groups  are  used  as  arguments  in communicator-building  functions. MPI does  not  provide  a  mechanism  to  build  a  group from scratch, but only from other, previously defined groups. 

**MPI_COMM_GROUP** accesses the group associated with given communicator.
```c
MPI_COMM_GROUP(comm, group)
```
- IN comm, communicator (handle)
- OUT group, group corresponding to comm (handle)

**C version**
```c
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group)
```

Some useful functions are the set-like operations (definition -> c syntax): 
- **MPI\_GROUP\_UNION** 
    ```c 
    int MPI_Group_union(MPI_Group group1, MPI_Group group2,MPI_Group *newgroup)
    ```
- **MPI\_GROUP\_INTERSECTION** 
    ```c 
    int MPI_Group_intersection(MPI_Group group1, MPI_Group group2,MPI_Group *newgroup)
    ```
- **MPI\_GROUP\_DIFFERENCE**  
    ```c 
    int MPI_Group_difference(MPI_Group group1, MPI_Group group2,MPI_Group *newgroup)
    ```
- **MPI\_GROUP\_INCL**  
    ```c 
    int MPI_Group_incl(MPI_Group group, int n, const int ranks[],MPI_Group *newgroup)
    ```
    The function MPI\_GROUP\_INCL creates a group newgroup that consists of then processes in group with ranks ranks[0],..., ranks[n-1]; the process with _i_ in newgroup is the process with rank ranks[i] in group.
- **MPI\_GROUP\_EXCL** 
    ```c 
    int MPI_Group_excl(MPI_Group group, int n, const int ranks[],MPI_Group *newgroup
    ```
    The function MPI\_GROUP\_EXCL creates a group of processes newgroup that is obtained by deleting from group those processes with ranks ranks[0] ,...ranks[n-1].  The ordering of processes in newgroup is identical to the ordering ingroup.

### Group Destructors

**MPI_GROUP_FREE** marks the group object for deallocation.
```c
MPI_GROUP_FREE( group)
```
- INOUT group, group (handle)

**C version**
```c
int MPI_Group_free(MPI_Group *group)
```

### Example: MPI groups

The following example uses the MPI\_Comm\_create\_group, which is a function that returns a new communicator for a group of processes. This function is described in the next section.

The following example uses 14 processes.
@[MPI GROUP]({"stubs": ["4/groups.c"], "command": "/bin/bash /project/target/4/groups.sh"})

## Communicator Management

As described in the Introduction, at the start of an MPI program all its processes belong to the communicator MPI\_COMM\_WORLD. Processes in the communicator have unique numbers (identifiers) in the interval between 0 and p-1, where p is the number of processes executed. In many application we want to partition processes into n subgroups forming separate communicators. Each communicator should include the processes belonging a particular task.

The standard type of communicator is known as an intra-communicator, but a second, more exotic type known as an inter-communicator, whcih provide communication between two different communicators. The two types differ in two ways:
1. An intra-communicator refers to a single group, an inter-communicator refers to a pair of groups. The group of an intra-communicator is simply the set of all processes which share that communicator. A communicator is a opaque object of type **MPI\_Comm**.
2. Collective communications (see next Chapter) can be performed with an intra-communicator. They cannot be performed on an inter-communicator. The group of processes involved in a collective communication is simply the group of the intra-communicator involved.

Inter-communicators are more likely to be used by parallel library designers than application developers. The routines MPI\_COMM\_SIZE and MPI\_COMM\_RANK can be used with inter-communicators, but the interpretation of the results returned is slightly different. An  intra-communicator  involves  a  single  group  while  an  inter-communicator  involvestwo  groups. However, in this book, we will focus only on intra-communicator communication functionalities.

**MPI\_COMM\_SIZE** compute the number of processes in a communicator.
```c
MPI_COMM_SIZE(comm, size)
```
- IN comm, communicator (handle)
- OUT size, number of processes in the group of comm (integer)

**C version**
```c
int MPI_Comm_size(MPI_Comm comm, int *size)
```

**MPI\_COMM\_RANK** compute the associated rank of process in a communicator.
```c
MPI_COMM_SIZE(comm, size)
```
- IN comm, communicator (handle)
- OUT rank, ank of the calling process in group of comm (integer)

**C version**
```c
int MPI_Comm_rank(MPI_Comm comm, int *rank)
```

**MPI\_COMM\_COMPARE** compares two communicators.
```c
MPI_COMM_COMPARE(comm1, comm2, result)
```
- IN comm1, first communicator (handle)
- IN comm2, second communicator (handle)
- OUT result, result (integer)

**C version**
```c
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result)
```

MPI\_IDENT results if and only if comm1 and comm2 are handles for the same object (identical groups and same contexts). MPI\_CONGRUENT results if the underlying groups are identical in constituents and rank order; these communicators differ only by context. MPI\_SIMILAR results if the group members of both communicators are the same but the rank order differs. MPI\_UNEQUAL results otherwise.

### Communicator Constructors

The  following  are  collective  functions  that  are  invoked  by  all  processes  in  the  group  or groups associated with comm, with the exception of MPI\_COMM\_CREATE\_GROUP, which is invoked only by the processes in the group of the new communicator being constructed.

**MPI_COMM_DUP(comm, newcomm)** duplicates  the  existing  communicator comm with  associated  keyvalues, topology information, and info hints. For each key value, the respective copy callback function determines the attribute value associated with this key in the new communicator; one particular action that a copy callback may take is to delete the attribute from the newcommunicator.

```c
MPI_COMM_DUP(comm, newcomm)
```
- IN comm,  communicator (handle)
- IN newcomm, copy communicator (handle)


**C version**
```c
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm)
```


**MPI_COMM_CREATE(comm, group, newcomm)** creates a new communicator.

```c
MPI_COMM_CREATE(comm, group, newcomm)
```
- IN comm, communicator (handle)
- IN group, group, which is a subset of the group of comm (handle)
- OUT newcomm, new communicator (handle)

**C version**
```c
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
```
If comm is  an  intra-communicator,  this  function  returns  a  new  communicator newcomm with communication group defined by the group argument. No cached information propagates from comm to newcomm.  Each process must call MPI\_COMM\_CREATE with a group argument  that  is  a  subgroup  of  the group associated  with comm;  this  could  be MPI\_GROUP\_EMPTY.  The  processes  may  specify  different  values  for  the group argument. If  a  process  calls  with  a  non-empty group then  all  processes  in  that group must  call  the function with the same grou pas argument, that is the same processes in the same order. Otherwise,  the call is erroneous.  _This implies that the set of groups specified across the processes must be disjoint._  If the calling process is a member of the group given as group argument, then newcomm is a communicator with groupas its associated group.  In the case that  a  process  calls  with  a group to  which  it  does  not  belong,  e.g.,MPI\_GROUP\_EMPTY, then MPI\_COMM\_NULL is  returned  as newcomm.   _The  function  is  collective  and  must  be called by all processes in the group of comm._

**This function must be called by all processes in the communicator**

**MPI_COMM_CREATE(comm, group, newcomm)** creates a new communicator.

```c
MPI_COMM_CREATE_GROUP(comm, group, tag, newcomm)
```
- IN comm, communicator (handle)
- IN group, gorup, which is a subset of the group of comm (handle)
- IN tag, tag (integer)
- OUT newcomm, new communicator (handle)

**C version**
```c
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag,MPI_Comm *newcomm)
```
It is similar to MPI_COMM_CREATE but can be called by all processes in the group.  In  addition, MPI\_COMM\_CREATE\_GROUP requires that comm is an intra-communicator. MPI\_COMM\_CREATE\_GROUP returns a new intra-communicator, newcomm,  for  which  the group argument  defines  the  communication group.   No  cached  information  propagates  from comm to newcomm.   Each  process  must provide  a  group  argument  that  is  a  subgroup  of  the  group  associated  withcomm;  this could be MPI\_GROUP\_EMPTY. The tag argument does not conflict with tags used in point-to-point communication andis not permitted to be a wildcard. 

**MPI_COMM_SPLIT(comm, color, key, newcomm)** partitions the group associated with comm into disjoint subgroups, one foreach value of color.

```c
MPI_COMM_SPLIT(comm, color, key, newcomm)
```
- IN comm, communicator (handle)
- IN color, control of subset assignment (integer)
- IN key, control of rank assigment (integer)
- OUT newcomm, new communicator (handle)

**C version**
```c
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm)
```
Each subgroup contains all processes of the same color.  Within each subgroup,  the  processes  are  ranked  in  the  order  defined  by  the  value  of  the  argument key,  with  ties  broken  according  to  their  rank  in  the  old  group.   A  new  communicator  iscreated for each subgroup and returned in newcomm.  A process may supply the color value MPI\_UNDEFINED, in which case newcomm returns MPI\_COMM\_NULL. This is a collective call, but each process is permitted to provide different values for color and key. 

### Communicator Destructors

**MPI_COMM_FREE** marks the communication object for deallocation.

```c
MPI_COMM_FREE(comm)
```
- INOUT comm, communicator to destroyed (handle)
**C version**
```c
int MPI_Comm_free(MPI_Comm *comm)
```
Any pending operations that use this communicator will complete normally; the object is actually deallocated only if there are no other active references to it. 

## Example: Groups and communicators management

The following example uses collective operations named MPI\_Allreduce, which will be described in the next Chapter. For what concerns this example you can consider that this function is able to sum all values inside an array held by each MPI process.

The following example uses 8 processes.
@[MPI_GROUP]({"stubs": ["4/groupsandcomm.c"], "command": "/bin/bash /project/target/4/groupsandcomm.sh"})

 -->