:- use_module(library(lists)).  


getFastestPath(I, M, FP):- 
	setof(Tam-Path, (dfs(I, M, Path), length(Path, Tam)), L), 
	nth0(0, L, FP).  





















