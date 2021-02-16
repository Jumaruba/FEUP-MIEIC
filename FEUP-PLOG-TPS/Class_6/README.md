# Class_6

In this class we are seeing some useful functions.   

```prolog
functor(Term, Name Arity).  
arg(Num, Term, Value).  
Term = ..List
```


```prolog
functor(ligado(a,b), ligado,2). 
arg(2, ligadoa(a,b), b).    
ligado(a,b) = ..[ligado,a,b]. 
```   

The last tem is a little differnet. Another example.  

```prolog 
T = ..[pred,a,X], T.  
``` 


### Map  

Call a predicate for every single element of a list.  
```prolog
f(X,Y):- Y is X*X. 

map([2,4,8], f, L). 
```


