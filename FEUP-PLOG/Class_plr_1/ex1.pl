:-use_module(library(clpfd)).  
:-use_module(library(lists)).

% the generic case 
generic(Vars, Size):-   
	MaxDomain is Size*Size,  
	length(Vars, MaxDomain),
	domain(Vars,1,MaxDomain),   
	all_distinct(Vars), 
	labeling([], Vars).  

equality_restriction(Array, EqualSum):-
	sum_list(Array, Sum), 
	Sum #= EqualSum.  


 






	

     


	






	
