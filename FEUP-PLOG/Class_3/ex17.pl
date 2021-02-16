:-use_module(library(lists)). 
% a) The easiest way to implement it is to use the inversion function. 
 
palindrome(X):-
	reverse(X, NX), 
	X = NX.  


