


dropN(L, N, S):- 
	dropN(L, N, N, S). 
	

dropN([X|L], Acc, N, [X|S]):-  
	Acc \= 1,  
	Acc1 is Acc-1,
	dropN(L, Acc1, N, S). 

dropN([X|L], 1, N, S):-  
	Acc is N,  
	dropN(L, Acc, N, S). 



dropN([], X, N, []). 
