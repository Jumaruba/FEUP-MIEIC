/* Factorial: 

Doing problems using the recursive call as the last action makes the program faster. 
*/  

% N => indice 
% A => answer  

% solution 1. 

fact(N, A):- fact(N, 1, A). 

fact(0, Acc, Acc). 
fact(N, Acc, A):-  
	N > 0,
	Acc_ is Acc*N,
	N_ is N-1, 
	fact(N_, Acc_, A).  

% solution 2. 

fact_(0, 1). 
fact_(N, A):-
	N > 0, 
	N_ is N-1, 
	fact(N_, A_),
	A is N*A_.  


/* Fibonnacci: */ 

% N => indice 
% A => answer 

% solution  

fib_(0,1). 
fib_(1,1).
fib_(N,A):- 
	N >= 2, 
	N_1 is N-1, 
	N_2 is N-2, 
	fib_(N_1, A_1),
	fib_(N_2, A_2), 
	A is A_1 + A_2.  

	







