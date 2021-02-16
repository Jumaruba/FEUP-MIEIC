# Exercise 09

First, to we get the returned value by the child process we need to do: 

```c
#include <sys/wait.h>   //wait
#include <sys/types.h>

...
    int status; 
    pid_t pid = fork();     
    if (pid >0){ //father's process
    waitpid(pid, &status, WUNTRACED); 
    printf("End value of the child: %d", WEXITSTATUS(status)); 
}
```

Remember that `status` is nothing more than a set of bytes where each position has a meaning.  
The macro `WEXITSTATUS` applies a mask that shows the position equivalent to the returned value of the child 
process.