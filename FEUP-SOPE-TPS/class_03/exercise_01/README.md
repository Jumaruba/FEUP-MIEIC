# Exercise 01 

This is a breaf explanation of the exercise 01. 

## First run 
```
father PID = 200; PPID = 7
son PID = 201; PPID = 200
PID = 200 - global = 2 ; local = 1
PID = 201 - global = 0 ; local = 3
```
## Second run 
```
father PID = 202; PPID = 7
son PID = 203; PPID = 202
PID = 202 - global = 2 ; local = 1
PID = 203 - global = 0 ; local = 3 
```

Basically the PPID is the id of the father.  
For the second run the father has the PID 202, so the son has the PPID 202.  

