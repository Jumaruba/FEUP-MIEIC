/*
	Find the K'th element of a list.
    The first element in the list is number 1.
    Example:
    ?- element_at(X,[a,b,c,d,e],3).
    X = c
	*/


element_at(X, [Y|Ys], Pos):-
	Pos >= 0,
	Pos_ is Pos-1, 
	element_at(X, Ys, Pos_).  
element_at(X, [X|Ys], 1). 	