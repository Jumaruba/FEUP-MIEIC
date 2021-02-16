# Letter c

Pressing ctrl + c in the terminal, we finish all the process (including the child).  
By other hand, using the command kill in the terminal, we just finish the parent process, but the child process 
were inherited by another process. 

__Why?__  

`^C` sends a `SIGINT` to all the processes in the foreground process group. To do the equivalent with `kill`, you should 
send the signal to the process group (OS-level concept):

```bash
kill -SIGINT -<pid>
```

source: [link](https://stackoverflow.com/questions/8398845/what-is-the-difference-between-ctrl-c-and-sigint)