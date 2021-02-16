:-use_module(library(lists)). 
ligado(a,b). 
ligado(f,i).
ligado(a,c). 
ligado(f,j).
ligado(b,d). 
ligado(f,k).
ligado(b,e). 
ligado(g,l).
ligado(b,f). 
ligado(g,m).
ligado(c,g). 
ligado(k,n).
ligado(d,h). 
ligado(l,o).
ligado(d,i). 
ligado(i,f).  

/* DFS ---------------------------------------------*/  

/**
 * @param I: Initial node.
 * @param M: Meta node.  
 * @param P: Complete path.
 */ 
dfs(I, M, P):-  
	dfs([], I, M, P).    

/**
 * @param V: Visited nodes. 
 * @param I: Initial node.
 * @param M: Meta node.  
 * @param P: Complete path. 
 */   
dfs(V, I, M, [I|P]):-
	\+member(I, V), 
	I \= M, 
	ligado(I, C), 
	dfs([I|V], C, M, P).

dfs(V, M, M, [M]).  


/* BFS --------------------------------------------*/  
/**
 * @param I: Initial node. 
 * @param M: Meta node. 
 * @param FP: Array final path.  
 */  

bfs(I, M, FP):-  
	bfs([], [[I]], M, P), 
   	reverse(P, FP). 	


/**
 * @param V: Visited nodes array. 
 * @param I: first element of the current array path. 
 * @param M: Meta node. 
 * @param FP: Final path. 
 */ 
bfs(V, [[I|IP]|Ps], M, FP):- 
 	\+member(I, V), 
	I \= M, 
	findall(J, ligado(I,J), L), 
	create_paths(L, [I|IP], New_FPs),  
	append(Ps, New_FPs, New_FP), 
	bfs([I|V], New_FP, M, FP). 

bfs(V, [[M|IP]|Ps], M, [M|IP]). 



/**
 * @param LN: List of Nodes. 
 * @param IP: The rest of the list with header I. 
 * @param F:  Final result. 
 */ 
create_paths([N|LN], IP, [L|F]):-  
	append([N], IP, L), 
	create_paths(LN, IP, F). 

create_paths([], IP, []). 












