use_module(library(lists)). 


pack(L1, X):-  
	pack_aux(L1, [], X). 

pack_aux([X,Y|L1], CL, FL):-
	X == Y, 
	append([X], CL, Temp), 
	pack_aux([Y|L1], Temp, FL).  

pack_aux([X,Y|L1], CL, FL):-
	X \= Y, 
	append([X], CL, Temp), 
	append(Temp, FL, New), 
	pack_aux([Y|L1], [], New). 
