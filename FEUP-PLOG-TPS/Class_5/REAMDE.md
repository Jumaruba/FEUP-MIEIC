# Class_5
In this class we have learned the concept of ! in prolog.  

```prolog 
not(X) :- X, !, fail. 
not(X). 
```

If X is false, we return to the `not(X)`. 
If it's true, so we have a fail and it will not performe the backtracking, since it will achieve the !.  

What if we did not have the ! in the program above? 
It will try the `not(X)` and will return `yes` in the same way. 
This is a `red cut`. If we eliminate it from the code, it will change the program logic. 

Remember that the fail clause will always track a backtracking.  
So, if we had: 

```prolog
not(X):- X, fail, X. 
not(X). 
```

I would return `yes`. 
