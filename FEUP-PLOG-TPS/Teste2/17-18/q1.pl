:- use_module(library(lists)).
:- use_module(library(between)).
prog1(N,M,L1,L2) :-
	length(L1,N),
	N1 is N-1, length(L2,N1),
	findall(E,between(1,M,E),LE),
	fill(L1,LE,LE_),
	fill(L2,LE_,_),
	check(L1,L2).
	
fill([],LEf,LEf).
fill([X|Xs],LE,LEf) :-
	select(X,LE,LE_),
	fill(Xs,LE_,LEf).
	
check([_],[]).
check([A,B|R],[X|Xs]) :-
	A+B =:= X,
	check([B|R],Xs).
	
	
% O programa gera duas listas. 
% A lista L1 tem tamanho N e a lista L2 tem tamanho N-1 
% As listas possuem elementos distintos no intervalo [1,M] e as duas 
% listas não podem conter um mesmo elemento em comum. 

% Logo a soma de elementos consecutivos de indices N e N+1  na lista L1, 
% deve ser igual ao elemento de indice N na lista L2. 

% Dominio: M 
% Tamanos N e N-1 

% M^(N + N -1) 




prog2(N,M,L1,L2) :-
	length(L1,N),
	N1 is N-1, length(L2,N1),
	
	domain(L1,1,M),
	domain(L2,1,M),
	append([L1,L2], Total), 
	all_distinct(Total),
	check1(L1,L2),
	labeling([],L1).

check1([_],[]).
check1([A,B|R], [X|Xs]):-
	A + B #= X, 
	check1([B|R], Xs). 