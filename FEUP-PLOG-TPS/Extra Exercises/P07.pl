/* Flatten a nested list structure.
    Transform a list, possibly holding lists as elements into a `flat' list by replacing each list with its elements (recursively).

    Example:
    ?- my_flatten([a, [b, [c, d], e]], X).
    X = [a, b, c, d, e]
	
	Hint: Use the predefined predicates is_list/1 and append/3
*/ 

use_module(library(lists)).

my_flatten([X|Xs], Ys):-  
	my_flatten(X, L1),
	my_flatten(Xs, L2),
	append(L1, L2, Ys). 
	
	
my_flatten([X|Xs], [X|Ys]):-
	\+ is_list(X), 
	my_flatten(Xs, Ys). 
	

my_flatten([], []). 