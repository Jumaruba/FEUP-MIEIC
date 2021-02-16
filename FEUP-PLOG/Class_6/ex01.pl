:- use_module(library(lists)). 
%a) 

duplica(X,Y):- Y is 2*X. 
map_([X|L], Name, [Y|SL]):-  
	E=..[Name, X, Y],  
	E,  
	map_(L, F, SL). 

map_([], _, []).


	
	
