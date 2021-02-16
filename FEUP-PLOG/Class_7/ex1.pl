movimento(-2,-1). 
movimento(-2, 1). 
movimento(2, -1). 
movimento(2, 1). 

movimento(-1,-2). 
movimento(1, -2). 
movimento(-1, 2). 
movimento(1, 2). 

salto_cavalo(X/Y, NX/NY):-
	movimento(MovX, MovY), 
	NX is X + MovX, 
	NY is Y + MovY,
	NX >= 1,
	NX =< 8,
	NY >= 1, 
	NY =< 8. 
	
	
trajecto_cavalo([X]).
trajecto_cavalo([P1,P2|Traj]):-
	salto_cavalo(P1,P2), 
	trajecto_cavalo([P2|Traj]). 
	
	
trajecto_cavalo([2/1, M, 5/4, X, Y/8]).

	
	
	