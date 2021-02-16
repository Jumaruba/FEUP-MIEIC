:-use_module(library(clpfd)). 
:-use_module(library(lists)).

solve(Semana):-    
    Encadernadores = [EN1, EN2, EN3, EN4],  
    Escritorio = [ES1, ES2, ES3], 
    Embaladores = [EM1, EM2],  

    set_every_size(Encadernadores, 5), 
    set_every_size(Embaladores, 5), 
    set_every_size(Escritorio, 4), 
    append([Encadernadores, Escritorio, Embaladores], Horarios), 
    set_all_distinct(Horarios),  

    length(Semana, 7),  
    trabalhadores_por_dia(Semana), 

    append(Semana, Total),
    labeling([], Total).


set_every_size([], _).
set_every_size([X|Trab], Size):-
    length(X, Size), 
    set_every_size(Trab, Size). 

set_all_distinct([]). 
set_all_distinct([X|Trab]):-
    all_distinct(X), 
    set_all_distinct(Trab). 

embaladores_seguidos(Dias)

quatro_dias_seguidos([_,_,_]).
quatro_dias_seguidos([D1,D2,D3,D4|Dias]):-
    abs(D1-D2) + abs(D3-D2) + abs(D4-D3) #= X, 
    X #\= 3, 
    quatro_dias_seguidos([D2,D3,D4|Dias]). 