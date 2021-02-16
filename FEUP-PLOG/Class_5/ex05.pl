
unificavel([], X, []). 


unificavel([X1|L1], X, L2):- 
	X \= X1,  
	!,
	unificavel(L1, X, L2).  

unificavel([X1|L1], X, [X1|L2]):-    
	unificavel(L1, X, L2).

