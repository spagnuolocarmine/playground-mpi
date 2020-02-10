# The Message-Passing Model 

Each process has to send/receive data to/from other processes. For instance, consider the array of integers sorting the problem. Two processors divide the problem into two sub-problems, at the end the communicate and order the whole array.

![MPIINTSORTING](/img/sorting.png)

### MPI Simple communication model

![MPIINTSORTING](/img/sendreceive.png)

Data communication in MPI is like email exchange. One process sends a copy of the data to another process (or a group of processes), and the other process receives it. Communication  requires the following information:

-  Sender has to know:
	- Whom to send the data to (receiver’s process **rank**).
	- What **kind of data** to send (100 integers or 200 characters, etc).
	- A user-defined **tag** for the message (think of it as an email subject; allows the receiver to understand what type of data is being received).
- Receiver “might” have to know:
	- Who is sending the data, the **rank** of the process (if the receiver does not know; in this case sender rank will be **MPI_ANY_SOURCE**, meaning anyone can send).
	- What **kind of data** is being received (partial information is fine, for instance is possible to receive up to 1000 integers).
	- What the user-defined **tag** of the message is (OK if the receiver does
	not know; in this case tag will be **MPI_ANY_TAG**).
The following code describes the above concepts. Two processes exchange a char value by using the send/receive MPI primitive.

@[Send Receive]({"stubs": ["ptop/send_receive.c"], "command": "/bin/bash /project/target/ptop/run2_send_receive.sh"})



# MPI Types and Constants

In two communicating MPI processes: one task is performing a send operation and the other task is performing a matching receive operation. Notice that **matching** operation is the common and required way to explain this case. Moreover, when a send or receive operation is started we should say is **posted**.

```c
MPI_Send(buffer,count,type,dest,tag,comm)

MPI_Recv(buffer,count,type,source,tag,comm,status)
```


![MPIBUFFER](/img/buffer1.png)

As you can see in the picture MPI introduces a hidden (or partial hidden) memory level, this level corresponds to the system buffer. MPI exploits this system buffer to realize several communications modes, that will be described later in this chapter. MPI provides particular routines to manage this buffer and pre-allocate them for special purposes.

**MPI manages system memory that is used for buffering messages and for storing internal representations of various MPI objects such as groups, communicators, datatypes, etc. This memory is not directly accessible to the user, and objects stored there are opaque: their size and shape is not visible to the user. Opaque objects are accessed via handles, which exist in user space. MPI procedures that operate on opaque objects are passed handle arguments to access these objects. In addition to their use by MPI calls for object access, handles can participate in assignments and comparisons.**

In general, when you write a MPI program you use two kind of buffer: 

- **Application Buffers**, these buffers are allocated and managed by your application. These buffer are used to develop your program.

- **Internal Buffers**, these buffers are internal to MPI and may or may not even exist. There's nothing in the MPI Standard about these buffers or how they are supposed to act, how big they are supposed to be, etc. 

- **Secial Buffers**, there are other kinds of buffers that might provide special services, such as buffers on the network card that can speed up data transfers. The way these behave is usually specific to the type of network you're using.

##### MPI Buffers

 **MPI_Buffer_attach** sets the given buffer as the MPI buffer space. This buffer will then be used when sending messages in an asynchronous mode (_MPI_Bsend_ and _MPI_Ibsend_). The buffer attached must contain enough space for the messages to send plus the memory overhead generated when issuing each _MPI_Bsend_ or _MPI_Ibsend_, which is represented by the constant _MPI_BSEND_OVERHEAD_. The buffer attached to MPI must be detached after-use by calling MPI_Buffer_detach. Also, only one buffer can be attached at any given time.

 ```c
int MPI_Buffer_attach(void* buffer, int size);
```

 **MPI_Buffer_detach** removes the buffer currently attached to the MPI buffer space, which has been attached with MPI_Buffer_attach. MPI_Buffer_detach will block until all the messages contained in the attached buffer are sent. Note that detaching a buffer does not free the corresponding memory; it is the responsibility of the user to do so.

 ```c
int MPI_Buffer_detach(void* buffer, int size);
```

## MPI Naming Convention and Terms

MPI-1 used informal naming conventions. In many cases, MPI-1 names for C functions are of the form Class_action_subset, but this rule is not uniformly applied. In MPI-2, an attempt has been made to standardize names of new functions according to the following rules. In addition, the C++ bindings for MPI-1 functions also follow these rules. C function names for MPI-1 have not been changed.

1. In C, all routines associated with a particular type of MPI object should be of the form Class_action_subset or, if no subset exists, of the form Class_action. In Fortran, all routines associated with a particular type of MPI object should be of the form CLASS_ACTION_SUBSET or, if no subset exists, of the form CLASS_ACTION.

2. If the routine is not associated with a class, the name should be of the form Action_subset in C.

3. The names of certain actions have been standardized. In particular, Create creates a new object, Get retrieves information about an object, Set sets this information, Delete deletes information, Is asks whether or not an object has a certain property.

C  names for MPI-1 functions violate these rules in several cases. The most common exceptions are the omission of the Class name from the routine and the omission of the Action where one can be inferred.
MPI identifiers are limited to 30 characters (31 with the profiling interface). This is done to avoid exceeding the limit on some compilation systems.


When discussing MPI procedures the following semantic terms are used.

- **nonblocking** A procedure is nonblocking if the procedure may return before the operation completes, and before the user is allowed to reuse resources (such as buffers) specified in the call. A nonblocking request is started by the call that initiates it, e.g., MPI_ISEND. The word complete is used with respect to operations, requests, and communications. An operation completes when the user is allowed to reuse resources, and any output buffers have been updated; i.e. a call to MPI_TEST will return flag = true. A request is completed by a call to wait, which returns, or a test or get status call which returns flag = true. This completing call has two effects: the status is extracted from the request; in the case of test and wait, if the request was nonpersistent, it is freed. A communication completes when all participating operations complete.
**blocking** A procedure is blocking if return from the procedure indicates the user is allowed to reuse resources specified in the call.
**local** A procedure is local if completion of the procedure depends only on the local executing process.
**non-local** A procedure is non-local if completion of the operation may require the execution of some MPI procedure on another process. Such an operation may require communication occurring with another user process.
**collective** A procedure is collective if all processes in a process group need to invoke the procedure. A collective call may or may not be synchronizing. Collective calls over the same communicator must be executed in the same order by all members of the process group.
**predefined** A predefined datatype is a datatype with a predefined (constant) name (such as MPI_INT, MPI_FLOAT_INT, or MPI_UB) or a datatype constructed with MPI_TYPE_CREATE_F90_INTEGER, MPI_TYPE_CREATE_F90_REAL, or MPI_TYPE_CREATE_F90_COMPLEX. The former are named whereas the latter are unnamed.
**derived** A derived datatype is any datatype that is not predefined.
**portable** A datatype is portable, if it is a predefined datatype, or it is derived from a portable datatype using only the type constructors MPI_TYPE_CONTIGUOUS, MPI_TYPE_VECTOR, MPI_TYPE_INDEXED, MPI_TYPE_INDEXED_BLOCK, MPI_TYPE_CREATE_SUBARRAY, MPI_TYPE_DUP, and MPI_TYPE_CREATE_DARRAY. Such a datatype is portable because all displacements in the datatype are in terms of extents of one predefined datatype.
**equivalent** Two datatypes are equivalent if they appear to have been created with the same sequence of calls (and arguments) and thus have the same typemap. Two equivalent datatypes do not necessarily have the same cached attributes or the same names.

 
## MPI Data Types

## MPI Constants

