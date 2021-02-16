# SOPE-proj2

## How to run

- To compile both the client and the server run `make`. You can compile only the client or the server using `make u` and `make q`, respectively.
- To run the client, type `./U2 <-t time> [-i threadInterval] [-d maxDuration] fifoname`. The threadInterval and maxDuration (maximum occupation time in the bathroom) must be specified in milliseconds.
- To run the server according to the first specification, type `./Q2 <-t time> [-f] fifoname`. The `-f` flag creates the FIFO even if it already exists.
- To run the server according to the second specification, type `./Q2 <-t time> [-l nplaces -n nthreads] [-f] fifoname`.
- `make clean` is available to remove all object files and `make remove` to also delete the `q` and `u` executables.   

## Relevant evaluation issues

Due to the server having a named semaphore to indicate the request FIFO is available for writing, our client thread always checks if it can open the semaphore, if it fails, we assume the server either isn't available or no longer accepts requests. This makes the client be able to print `FAILD` and stop sending requests, even though it didn't write `CLOSD`. This could possibly lead to other discrepancies.

## Part 1 vs part 2 disclaimer

Our server program supports both specifications; as such, the server only initializes and uses the extra resources required for part 2 whenever both `-l` and `-n` are specified.

Therefore, many parts of this README will also explain a lot of the structure and code required by the second part.

## Context 

The goal of this project is to create a client-server application, that should handle conflicts between shared zones.   
The shared zone consists of a bathroom with several unisex `places`, controlled by a process Q, which receives the requests from the client, sent by a multithreaded U (client) process (or multiple).  
The client indicates in each request how much time they will spend in the bathroom, then the server must handle the several requests sent by the client. 
The second specification restricts both the number of concurrent server threads and the number of available bathrooms.

## Features implemented 

All requested features were fully implemented and all resources are released upon termination, except when the user terminates using a SIGINT, when most resources are liberated, but some may not be. 

## Known errors and bugs 

Currently a "bug" is still present, it occurs when an unexpected/unhandled error happens or when the user `SIGINTS` either the client or the server (alongside some pretty bad luck regarding where the program was interrupted).

This can cause the other program to block on an `open()` call, effectively blocking a thread (and also a bathroom in the server's case) possibly forever. This bug is rather hard to work around, as it would require a major change to the structure of the program, since all threads are detached right after being created, and killing a detached thread is agreed upon to not be possible. As such, we would need to keep track of all our threads, and join them whenever necessary (and distinguish when they've exited or they're stuck, in order to kill them instead).

## Implementation details  

### Client implementation 

The main program of the client was created in the file `u.c`, however the function to parse the arguments from the command line was implemented at `u_parseArgs.c`.   
The `user` function, which is always launched as a thread by the main loop, represents a single request.

Each one of these threads is responsible for initializing the private FIFO (it is created before writing the request to the server to guarantee the latter won't fail its `open()` call of the client's FIFO).
The client then writes the `Request` struct to the public FIFO and awaits a response.

### Server implementation 

The main program of the server was created in the file `q.c`, however the function to parse the arguments from the command line was implemented at `q_singleton.c`. Given the necessity to the threads to access some of these command line arguments, even after the main thread has exited, we have turned them into a Singleton.

Upon starting the server, it creates the FIFO (overrides an old one if `-f` was used) and initializes a semaphore (explained further in [Busy waiting](#Busy-Waiting)). Afterwards a call to `alarm(nsecs)` is made, to ensure that if no client appears, the call to `open()` the FIFO won't block forever, effectively acting as a timeout. Once the call to open is done, we reset the alarm (`alarm(0)`) and check if the file descriptor was open successfully. If it wasn't, we check if errno was `EINTR`, in which case we proceed to normally shut down the server.  
This solution could not be used elsewhere, as alarms relate to a process and not to a thread.

The server creates the public fifo as soon as possible, for the clients to be able to run and send requests. Then, the server waits for the requests through a semaphore, using `sem_timedwait` (to avoid waiting infinitely).

After waiting for the semaphore, the server reads a request and sends a thread responsible for handling it and sending a response. The `client_handler` function represents the threads created to attend each client request.  

When the server terminates (nsecs passed), it stops accepting requests and for every request already written in the fifo, it rejects it and sends it back.

### Communication between client and server 

The client-server communication protocol was implemented by using the struct `Request` defined in the file `requests.h`.

### Busy waiting

To avoid busy waiting as much as possible, we have relied upon semaphores and the very nature of the `read()` and `write()` operations on pipes and the `open()` call on slow devices, in our case, FIFOs.

The server has a `requestSemaphore` named "*fifoname*.sem", to indicate to any clients that it's open to receive requests, and whenever the bathroom closes, this named semaphore is unlinked as soon as possible. According to the man page, `sem_unlink()` only deletes the semaphore when all processes/threads that currently have it open close it, but most importantly, it instantly removes the name of the semaphore from the list of named semaphores in the system, which allows any client that wants to connect that if the named semaphore cannot be opened, the server either never existed or the bathroom has already closed and the server is only dismissing the remaining requests (2LATE).

As mentioned before, `read()` and `write()` already block the call for us until the can complete their operation, avoiding the busy waiting altogether. `write()` blocks until either it has room to write in the FIFO. `read()` blocks until data is available. The are also a crucial part of our error detection, as `write()` sets errno to `EPIPE` when all read ends of the FIFO have been closed, and `read()` returns 0 when all the write ends of the FIFO have been closed.

#### Part 2

To ensure that the server launches a new thread as soon as possible without resorting to busy waiting, we have implemented two new unnamed semaphores, one regarding an available bathroom and the other a new thread can be launched.

These semaphores are decreased (using `sem_timedwait()` to ensure the bathroom isn't open for too long). The bathroom semaphore increased whenever a `clientHandler()` thread ends, and the thread semaphore is increased whenever a `clientHandler()` or `dismissClient()` thread ends.

### Operation log 

The handler to print the log operations was created in a separate file called `handle_log.c`. In this file there is just one function that receives the `request` struct and the string `oper` which indicates the operation. Then it calls the function time() to determine the instant and prints the log entry.

As rule of thumb, whenever the log relates to a received message, it has the process id and the thread id of the sender. Whenever a log relates to a sent message or a FAILD/GAVUP, it has the pid and the tid of the thread itself.

### Queue 

The queue implementation from Tiago's LCOM project and our previous `simpledu` was improved, now supporting variable maximum size.

This queue is used to keep track of which bathrooms are (not) occupied. At the start of the server, it fills the queue with all available bathrooms. As requests start coming in, the server pops the bathroom's number from the queue and gives it to the client. Upon the conclusion of the thread, it pushes the bathroom back into the queue.

A nice and intended side effect is that if the number of threads is lower than the number of bathrooms, the bathrooms will cycle between themselves, allowing time for our staff to clean them.

To prevent multiple threads accessing the queue at once (trying to push and pop something at the same time, to be precise), we have deployed a `pthread_mutex_t` dedicated to manage the access to it.

### Synchronization

All the `Request` writing operations have no additional syncronization thanks to the POSIX standard. POSIX.1-2001 guarantees PIPE_BUF to be at least 512 bytes, and in Linux it is currently 4096 bytes. As such, the standard guarantees that all writing operations smaller than PIPE_BUF are atomic. As our `Request` is only 24 bytes long, they will always be written to the Pipe contiguously.

### Resource Management

The Server has various global/singleton resources allocated in the heap, as such, to release them back to the system, we have used `at_exit()` to push a void `server_cleanup()` function that frees the singleton, the queue and all its data, as well as closing the remaining semaphores. This method is also called when sending a `SIGINT` signal.
