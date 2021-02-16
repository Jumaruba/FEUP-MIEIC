% create a predicate of permutations

% Selects a number and delete it from the list 
select(X, L1, L2):-
	append(K1, [X|K2], L1), 
	append(K1,K2, L2).  

permutation(L1, [X|L2]):-
	select(X, L1, Z),  		% selects the first element (random).
	permutation(Z, L2). 	% selects the first element of the other partitions.   

permutation([], []). 

% consult('ex12.pl'). 
% permutation([1,2,3,4], L). 


