%a) 

:-use_module(library(clpfd)). 

magic(Vars):-
	Vars = [V1, V2,V3,
			V4, V5,V6,
			V7,V8,V9], 
	domain(Vars, 1, 9), 
	all_distinct(Vars), 
	V1+V2+V3 #= V4+V5+V6, 
	V1+V2+V3 #= V7+V8+V9, 
	V1+V4+V7 #= V2+V5+V8, 
	V1+V4+V7 #= V3+V6+V9,
	V1+V5+V9 #= V3+V5+V7,
	V1 #< V3, V1 #< V7, V3 #< V7,
	
	labeling([], Vars).  