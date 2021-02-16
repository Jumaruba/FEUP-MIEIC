# Exercise 07

## Explanation 

We have used the command `execlp`.   
Let's see how it works.  

- When a `exec` command is executed the image of the program now turns out to be the 
program called by `exec`. So any code after the exec, turns out to be an error situation. 

```c
execlp("gcc", "gcc", prog, "-Wall", "-o", argv[1], NULL);
//from here and on is an error situation
printf("Error message");
exit(-1);
```

- The `execlp` has the letters `l` and `p` composing the word `exec`.  
The `l` means that we will give the arguments of the new program one by one.  
The `p` means that we need to give the name of the file. This file will be searched
at the files defined at the $PATH system. 
