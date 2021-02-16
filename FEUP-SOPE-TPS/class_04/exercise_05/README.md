# The SIGCHLD behavior 

There is a further possibility for dealing with dead child processes. Explicitly setting the disposition of SIGCHLD 
to SIG_IGN causes any child process that subsequently terminates to be immediately removed from the system instead of 
being converted into a zombie. In this case, since the status of the child process is simply discarded, a subsequent 
call to wait() (or similar) can’t return any information for the terminated child.  

On Linux, as on many UNIX implementations, setting the disposition of SIGCHLD to
SIG_IGN doesn’t affect the status of any existing zombie children, which must still be
waited upon in the usual way. On some other UNIX implementations (e.g., Solaris 8),
setting the disposition of SIGCHLD to SIG_IGN does remove existing zombie children.

Thus, on some older UNIX implementations,
ignoring SIGCHLD has no effect on the creation of zombies. The only completely portable
way of preventing the creation of zombies is to call wait() or waitpid(), possibly from
within a handler established for SIGCHLD.  

Font: The Linux Programming interface - A Linux and UNIX programming handbook

To ignore the signal we might set the sa_handler to SIG_IGN: 

```c
struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
```   