% a) Counts how many elements there is in the list 

conta([X|L], N):-
	conta(L, N1),
	N is N1 +1. 
conta([], 0).

% OR -- more efficient way: 

conta_(L, N):-
	conta(L, N, 0). 

conta_([X|L], N, Acc):- 
	Acc1 is Acc+1, 
	conta_(L, N, Acc1). 
conta_([], N, N). 

	
% conta([1,2,3,4], N).    

% b) Counts how many times an element appears in a list.

conta_elem(X, [X|L], N):-
	conta_elem(X, L, N1), 
	N is N1+1. 
conta_elem(X, [Y|L],N):-
	X \= Y, 
	conta_elem(X,L,N).
conta_elem(X,[], 0). 

% conta_elem(1,[1,2,3,4,2,1,2,1,2],N).  

% OR -- more efficient way 
conta_elem_(X, L, N):-
	conta_elem_(X, L, N, 0).  

conta_elem_(X, [X|L], N, Acc):-
	Acc1 is Acc+1, 
	conta_elem_(X,L, N, Acc1). 

conta_elem_(X, [Y|L], N, Acc):-
	X \= Y, 
	conta_elem_(X, L, N, Acc). 

conta_elem_(X, [], N, N).

% conta_elem_(1,[1,2,3,4,2,1,2,1,2],N).


% consult('ex08.pl').
