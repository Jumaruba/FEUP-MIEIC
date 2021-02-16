:- use_module(library(lists)). 
:- include('ex01.pl'). 

getAllPaths(I, M, P):-
	findall(Path, dfs(I, M, Path), P).  
