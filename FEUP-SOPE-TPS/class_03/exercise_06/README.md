# Exercise 06 


## Letter b  

To eliminate the zombie proccess we need to execute the following instruction: 
```c
int status; 
waitpid(-1, &status, WNOHANG); 
```

The `WNOHANG` parameter means that it will check if there is a child process that has already finished it's job 
(i.e a process zombie). If so, it will accept it's return value, else it will continue the code. 

In order to avoid zombie process I did this: 

```c
else // simulando o trabalho do pai
    for (j=1; j<=10; j++) {
        waitpid(-1, &status, WNOHANG); //checking each second if there's a zombie process
        sleep(1);
        printf("father working ...\n");
}
``` 

## Letter c

Eliminating the `exit` from the child process, this happens: 

```c
	for (i=1; i<=3; i++) {
		pid = fork();
		if ( pid < 0) {
            //case of error
		}
		else if (pid == 0) {
			//This process will not finish here, it will go to the loop again.  
            //In the end the child will generate new children. 
		}
		else // father's work
		}
	}
	exit(0);
}
```