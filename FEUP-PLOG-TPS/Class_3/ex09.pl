% a) Define substitutue(X, Y, L1, L2) that substitutes all the occurrences of X in L1 for Y in L2. 


substitui(X, Y, [X|L1], [Y|L2]):-  
	substitui(X, Y, L1, L2). 

substitui(X, Y, [Z|L1], [Z|L2]):- 
	X \= Z,  
	substitui(X, Y, L1, L2). 

substitui(X, Y, [], []). 

% substitui(1, 2, [1,2,3,4,1,2,1], L2). 


% b) Eliminates duplicates in L1. 

% Case 1: We just want to eliminate repeated elements. Supposing our list is [1,2,2,3], the result would be [1,2,3]. 

elim_dup_c1([X|L1], L2):-   
	member(X, L1), 
	elim_dup_c1(L1, L2). 
elim_dup_c1([X|L1], [X|L2]):-
	\+ member(X, L1), 
	elim_dup_c1(L1, L2). 
elim_dup_c1([], []). 

% elim_dup_c1([1,2,3,4,1,2], L).  

% Case 2: We wanna eliminate the duplicate elements. Supposing our list is [1,2,2,3], the result would be [1,3]. 

elim_dup_c2(L1, L2):-  
	elim_dup_c2(L1, L2, []). 

elim_dup_c2([X|L1], L2, Acc):-
	(member(X, L1); member(X, Acc)), 
	elim_dup_c2(L1, L2, [X|Acc]). 

elim_dup_c2([X|L1], [X|L2], Acc):-
	\+member(X,L1),\+ member(X, Acc),  
	elim_dup_c2(L1, L2, Acc). 

elim_dup_c2([], [], Acc). 

% elim_dup_c2([1,2,2,3,4,5,6,4], L2). 

% consult('ex09.pl').  



   


	

