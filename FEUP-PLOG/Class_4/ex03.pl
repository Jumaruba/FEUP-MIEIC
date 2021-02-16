
:- use_module(library(lists)). 
:- include('ex01.pl'). 
 

pathContains(L, P):-
	ligado(X,_),
	ligado(_,Y), 
	dfs(X,Y,P),
	all_member(L, P). 
	
/* 
 * All members of L1 is member of L2
 */ 
all_member([X|L1], L2):-   
	member(X, L2), 
	all_member(L1, L2).  

all_member([], L2). 
	
