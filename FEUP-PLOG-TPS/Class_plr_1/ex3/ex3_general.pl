:- use_module(library(clpfd)). 
:- use_module(library(lists)). 


queen(List, Size):-  
	length(List, Size), 
	domain(List, 1, Size),  
	all_distinct(List), 
	run_through_list(List), 
	labeling([], List). 


run_through_list([]). 
run_through_list([X|L]):-
	elem_cant_attack(L, X, 1), 
	run_through_list(L). 	

% The element Elem can't attack the other elements of the List. 
% Example:  
% Board  
%
% A1, A2, A3, A4 
% B1, B2, B3, B4 
% C1, C2, C3, C4 
% D1, D2, D3, D4  
%
% If there's one queen at B1, B1 can't attack A2 neither C2. 
% And B1 can't attack D3.   
%
% in List = [C1, C2, C3, C4], C1 = 2. So it can't attack C2 = 1, C2 = 3 and D3 = 4 (D3 = -1, which doesnt exist).   

elem_cant_attack([], _, _). 
elem_cant_attack([X|L], Elem, Diff):-   
	abs(X - Elem) #\= Diff, 
	NewDiff is Diff +1, 
	elem_cant_attack(L, Elem, NewDiff). 



	
