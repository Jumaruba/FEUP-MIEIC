
rodar(L, N, S):-    
	N < 0, 
	length(L, X),   
	sum_until_positive(N, X, N1), 
	rodar(L, N, S, 0).  
 
rodar(L, N, S):- 
 	N > 0, 
	rodar(L, N, S, 1). 


sum_until_positive(X, Y, Z):- 
	X1 < 0, 
	X1 is X + Y, 
	sum_until_positive(X1, Y, Z).   

sum_until_positive(X, Y, X):- X>0.


rodar([X|L], N, S, P):-   
	N > 0, 
	N1 is N -1,  
	append(L, [X], R), 
	rodar(R, N1, S, P). 

rodar(L, 0, L, P). 

