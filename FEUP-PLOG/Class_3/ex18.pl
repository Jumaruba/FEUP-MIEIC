%a) 

dup([X|L], [X,X|S]):-  
	dup(L, S). 

dup([], []).  

%b) 

dup_N([X|L], N, S):-   
	dup_N(L, N, S__), 
	dup_element_N(X, N, S_),   
	append(S_, S__, S).  

dup_N([], N, []). 

dup_element_N(X, N, [X|S]):-   
	N > 0, 
	N1 is N-1, 
	dup_element_N(X, N1, S). 

dup_element_N(X, 0, [X]). 

 	
