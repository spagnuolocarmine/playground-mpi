# Derived Datatypes

All  point  to  point  communications  use  only  buffers  containing  a sequence  of  identical  basic  datatypes.   This  is  too  constraining  on  two  accounts.   One  often wants to pass messages that contain values with different datatypes (e.g., an integer count, followed by a sequence of real numbers); and one often wants to send noncontiguous data  (e.g.,  a  sub-block  of  a  matrix).  

One  solution  is  to  **pack  noncontiguous**  data  into a  contiguous  buffer  at  the  sender  site  and  unpack  it  at  the  receiver  site.  This  has  the disadvantage of requiring additional memory-to-memory copy operations at both sites.  However, MPI provides mechanisms to specify more general, mixed, and **noncontiguous communication buffers**.  It is up to the implementation to decide whether data should be first packed in a contiguous buffer before being transmitted, or whether it can be collected directly from where it resides.

## Sending noncontiguous data using Pack and Unpack

OpenMPI provides pack/unpack functions for sending noncontiguous data.  The user explicitly packs data into a contiguous buffer before sending it, and unpacks it from a contiguous buffer after receiving it. However, is convient using derivated type. We will introduce pack/unpack routines for compatibility with previous libraries or code.  

