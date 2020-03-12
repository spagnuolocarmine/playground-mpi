# Group Management

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

## Group Constructors

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

## Group Destructors

**MPI_GROUP_FREE** marks the group object for deallocation.
```c
MPI_GROUP_FREE( group)
```
- INOUT group, group (handle)

**C version**
```c
int MPI_Group_free(MPI_Group *group)
```

# Example: MPI groups

The following example uses the MPI\_Comm\_create\_group, which is a function that returns a new communicator for a group of processes. This function is described in the next section.

@[MPI GROUP]({"stubs": ["4/groups.c"], "command": "/bin/bash /project/target/4/groups.sh"})
