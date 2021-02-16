/*Find the number of elements of a list.*/ 

list_size([], 0). 	
list_size([Y|Ys], s(X)):- 
	list_size(Ys, X). 

%or
 
size([], 0). 
size([Y|Ys], X):-
	size(Ys, X_), 
	X is X_+1. 