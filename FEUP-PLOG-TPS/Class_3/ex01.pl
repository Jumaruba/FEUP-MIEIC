% a)  search for a member 


member_(X, [X|L]). 
member_(X, [Y|L]):-   
	X != Y, 
	member_(X, L). 
	
% b) implementing it with append 
member_1(X,L):- 
	append(Z, [X|K], L).  


% c) returning the last element of the list 
last_(X, L):- 
	append(_, [X|[]], L).  
 

% d) finding the Kth term of the list     
kth(X, 1 ,[X|_] ). 
kth(X, N, [Y|L]):-    
	N > 1, 
	N_ is N-1, 
	kth(X, N_, L). 
	
	


