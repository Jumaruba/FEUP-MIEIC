/* Reverse a list */ 


reverse(Xs, Zs):-
	append_reverse(Xs, [], Zs). 
	
append_reverse([X|Xs], Ys, Zs):- 
		append_reverse(Xs, [X|Ys], Zs). 
		
append_reverse([], Ys, Ys). 
