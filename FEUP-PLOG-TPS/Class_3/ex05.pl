% a) Search for a member. 


member_(X, [X|L]). 
member_(X, [Y|L]):-   
	X != Y, 
	member_(X, L). 
	
% b) Implementing it with append. 
member_1(X,L):- 
	append(Z, [X|K], L).   

% c) Implementing last(L,X) using append just one time. 

last_(L,X):-
	append(K, [X], L). 

% d) Find the Nth member of the list. 

nth([X|L], X, 1). 
nth([Y|L], X, N):- 
	N > 0, 
	N1 is N-1,  
	nth(L, X, N1). 



