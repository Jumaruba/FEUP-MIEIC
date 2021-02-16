% tip just one queen in a column  

queen_4(List):-
	List = [C1, C2, C3, C4], 
	domain(List, 1, 4),  	% the value of each element is the position  
	all_distinct(List), 	% the elements can't be in the same line 
	% diagonals restrictions 
	abs(C1 - C2) #\= 1, abs(C1 - C3) #\= 2, abs(C1 - C4) #\= 3, 
	abs(C2 - C3) #\= 1, abs(C2 - C4) #\= 2,
	abs(C3 - C4) #\= 1, 

	labeling([], List). 

