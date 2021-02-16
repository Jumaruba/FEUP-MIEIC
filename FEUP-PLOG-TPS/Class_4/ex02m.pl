ligado(a,b,3).
ligado(a,c,4). 
ligado(c,d,2). 
ligado(b,d,2). 
ligado(d,e,3). 
ligado(b,e,7).  

:- use_module(library(lists)).   

/**
 * @param IN: Initial Node.  
 * @param MN: Meta Node.   
 * @param SP: Solution Path. 
 */ 
dij(IN, MN, SP, SC):-  
	dij([[IN]], [0] , MN, [], SP, SC).  

/**
 * @param MN: Meta Node. 
 * @param V: Visited array. 
 * @param SP: Solution path. 
 * @param C: Array of costs. 
 * @param CC: Current cost.  
 */ 
dij([[I|IP]|P], [CC|C], MN, V,  SP, SC):-   
	\+ member(I, V), 		% Node must not been visited before. 
	I \= MN, 
	findall(X, ligado(I, X, _), LLN), 	% Get the nodes linked to I. 
	findall(X, ligado(I, _, X), CLN), 	% Get the costs of the linked nodes.  
	create_paths([I|IP], CC, LLN, CLN, PIL, CIL), 
	insert_all_paths(P, [CC|C] , PIL, CIL, FP, FC), 
	dij(FP, FC, MN, [I|V], SP, SC). 

dij([[MN|L]|_], [CC|_], MN, _, [M|L], CC). 


create_paths(P, C, [LL|LLN], [CL|CLN], [[LL|P]|NewLLN], [NewC|NewCLN]):-  
	NewC is C+ CL, 
   	create_paths(P, C, LLN, CLN, NewLLN, NewCLN). 

create_paths(P, C, [], [], [], []).  
 
/** 
 * @brief: insert elements in the AP, keepping the respective costs in ascending order. 
 * @param AP: Arrays of paths.  
 * @param AC: Array of costs. 
 * @param PI: Path to insert. 
 * @param PIL: List of paths to insert  
 * @param CI: Cost to insert. 
 * @param CIL: List of costs to insert.  
 * @param FP: Final array of paths. 
 * @param FC: Final array of costs. 
 */ 
insert_all_paths(AP, AC, [PI|PIL], [CI|CIL], FP, FC):-  
	insert_path(AP, PI, AC, CI, FP_, FC_), 
	insert_all_paths(FP_, FC_, PIL, CIL, FP, FC). 

insert_all_paths(FP_, FC_, [], [], FP_, FC_).
insert_all_paths([], [],PIL, CIL, [CIL], [PIL]).   
insert_all_paths([], [0],PIL, CIL, [CIL], [PIL]).  

 
/*
 * @brief: insert one array in a list of path, keeppinh the array of costs in ascending order. 
 * @param P: Current path. 
 * @param PL: Path list.  
 * @param PI: Path to insert. 
 * @param C: Current Cost. 
 * @param CL: List of costs. 
 * @param CI: Cost to insert. 
 */
insert_path([P|PL], PI, [C|CL], CI, [PI, P|PL], [CI, C|CL]):-   
	CI =< C. 

insert_path([P|PL], PI, [C|CL], CI, [P|FP], [C|FC]):-   
	CI > C, 
	insert_path(PL, PI, CL, CI, FP, FC).  

insert_path([], PI, [], CI, [PI], [CI]).  
insert_path([], PI, [0], CI, [PI], [CI]). 



















