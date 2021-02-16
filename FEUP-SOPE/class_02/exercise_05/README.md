# Conclusions

## Exercise a

In the file p5a.c we have the following code for open:

```c
 fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600);
  write(fd,text1,5);
  write(fd,text2,5);
```

The macros have the following meaning:

```
O_CREAT : if the file doesn't exist, create it
O_WRONLY: write only
O_TRUNC : put's the size of the file as 0. It means that first it will clean the file before write on it
O_EXCL  : creates an error if the file exists and if O_CREAT was instatiated. It means that the   
file in question must be created by the program
O_SYNC  : the write operations just return after the data be transfered to the disk
```

While in p5b.c we just have:

```c
  fd = open("f1.txt", O_WRONLY|O_SYNC,0600);
  write(fd,text1,5);
  write(fd,text2,5);
```

Which means that the file will not be created and it will not put the size to 0. It will just overwrite the information on it 
starting from position 0. 

## Exercise b

- First I have added a check error to the file p5a.c: 

```c
  if ((fd = open("f1.txt",O_CREAT|O_TRUNC|O_WRONLY|O_EXCL|O_SYNC,0600)) < 0){
    perror("The file already exists");
    exit(1);
  }
``` 

Then I have executed the exercise p5a.c twice. This is the output: 

```
The file already exists: File exists
```

- Now removing O_EXCL and executing again, no errors are returned. 
- Changing the content to be written: 

```c
  char *text1="AAA";
  char *text2="Ane";
```

Executing the code again, we have concluded that the macro __O_TRUNC really cleans the file before write__. 

- Changing again the content to be written and removing the macro O_TRUNC our code look like this: 

```c
  char *text1="B";
  char *text2="D";

  if ((fd = open("f1.txt",O_CREAT|O_WRONLY|O_SYNC,0600)) < 0){
    perror("The file already exists");
    exit(1);
  }
  write(fd,text1,1);
  write(fd,text2,1);
  ```

  And with this, we conclude that the content was overwritten. 

  - Now let's add the macro O_APPEND to our code. 

```c
  if ((fd = open("f1.txt",O_CREAT|O_WRONLY|O_APPEND|O_SYNC,0600)) < 0){
    perror("The file already exists");
    exit(1);
  }

```

With this we have added new words __in the end of the file__. 
So, before we had something like this: `BDAAne`.  
Now, it's like this: `BDAAneAAAAABBBBB`

- Executing both files at the same time with O_SYNC we have that they don't overwrite each other and the sequence of the word is consecutive. By another hand, removing O_SYNC implies that the sequence will not be consecutive and both programs can overwrite what each other has written.  
