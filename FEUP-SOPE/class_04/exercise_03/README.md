# The SIGCHLD signal 


This signal is sent (by the kernel) to a parent process when one of its children
terminates (either by calling exit() or as a result of being killed by a signal). It
may also be sent to a process when one of its children is stopped or
resumed by a signal.  

Making repeated nonblocking waitpid() calls wastes CPU time and adds complexity to an
application design. To get around these problems, we can employ a handler for the
SIGCHLD signal.  








# References 

The Linux Programming interface - A Linux and UNIX programming handbook 