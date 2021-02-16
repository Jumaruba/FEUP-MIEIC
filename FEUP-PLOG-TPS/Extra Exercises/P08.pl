/* Eliminate consecutive duplicates of list elements.
    If a list contains repeated elements they should be replaced with a single copy of the element. The order of the elements should not be changed.

    Example:
    ?- compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
    X = [a,b,c,a,d,e]
	
	listining(x) 
	spy x 
	debug 
	*/
	
	
compress([X],[X]).  
compress([X,X|Xs], Ys):-
	compress([X|Xs], Ys). 
compress([X,Y|Xs], [X|Ys]):-
	X \== Y, 
	compress([Y|Xs], Ys). 