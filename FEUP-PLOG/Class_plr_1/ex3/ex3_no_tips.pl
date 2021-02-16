:-use_module(library(clpfd)). 
:-use_module(library(clpfd)). 

% solution without tips
queen_4_sol1(List):- 
	List = [A1, A2, A3, A4,
			B1, B2, B3, B4, 
			C1, C2, C3, C4, 
			D1, D2, D3, D4],  
	domain(List, 0, 1),    
	sumList(List, 4), 
	% assert interval in columns 
	A1 + B1 + C1 + D1 #=< 1, 
	A2 + B2 + C2 + D2 #=< 1, 
	A3 + B3 + C3 + D3 #=< 1,
	A4 + B4 + C4 + D4 #=< 1,  
	% assert interval in lines 
	A1 + A2 + A3 + A4 #=< 1, 
	B1 + B2 + B3 + B4 #=< 1, 
	C1 + C2 + C3 + C4 #=< 1, 
	D1 + D2 + D3 + D4 #=< 1, 
	% assert diagonals right to left
	B1 + A2  #=< 1, 
	C1 + B2 + A3 #=< 1, 
	D1 + C2 + B3 + A4 #=< 1, 
	D2 + C3 + B4 #=< 1, 
	D3 + C4 #=< 1, 
	% assert diagonals left to right 
	C1 + D2 #=< 1, 
	B1 + C2 + D3 #=< 1, 
	A1 + B2 + C2 + D4 #=< 1, 
	A2 + B3 + C4 #=< 1, 
	A3 + B4 #=< 1, 

	% get solution 
	labeling([], List). 
	
sumList([X], Sum):- 
	X #= Sum. 

sumList([X|L], Sum):-   
	NewSum #= Sum -X, 
	sumList(L, NewSum). 


