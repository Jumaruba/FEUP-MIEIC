:- use_module(library(lists)). 
%a)  

functor2(Term,F,Arity):- 
	Term =..[F|X],  
	length(X, Arity). 

%b) 
arg_(N, Term, Arg):- 
	Term =..[F|X],   
	nth1(N, X, Arg). 

	
	
