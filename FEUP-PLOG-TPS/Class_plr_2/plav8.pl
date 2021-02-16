:-use_module(library(clpfd)). 
:-use_module(library(lists)).

solve(SumLinhas, SumColunas, Matriz):-  
    length(SumLinhas, Tamanho),
    length(SumColunas, Lado),
    cria_matriz(Matriz, Tamanho, Lado), 

    append(Matriz, Variaveis), 
    domain(Variaveis, 0, 1), 
    
    sums(SumLinhas, Matriz), 
    transpose(Matriz, Transponsed),
    sums(SumColunas, Transponsed),

    labeling([], Variaveis). 

cria_matriz([], 0, _):- !.
cria_matriz([X|Matriz], Tamanho, Size):-
    length(X, Size), 
    NewTamanho is Tamanho -1, 
    cria_matriz(Matriz, NewTamanho, Size).  

sums([], []). 
sums([Sum|Sums], [Linha|Matriz]):-
    sum(Linha, #=, Sum), 
    sums(Sums, Matriz). 