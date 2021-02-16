:-use_module(library(clpfd)). 
:-use_module(library(lists)).
solve(Variaveis):-
    Variaveis = [
        ComumInglesHistoria, ComumInglesLiteratura, 
        DuraInglesHistoria, DuraInglesLiteratura, 
        ComumFrancesHistoria, ComumFrancesLiteratura, 
        DuraFrancesHistoria, DuraFrancesLiteratura
    ],  
    domain(Variaveis, 0, 1000), 
    % historia 
    ComumInglesHistoria + DuraInglesHistoria + ComumFrancesHistoria + DuraFrancesHistoria #= 52, 
    ComumInglesHistoria + DuraInglesHistoria #= 27,  
     
    % dura 
    DuraInglesHistoria + DuraInglesLiteratura + DuraFrancesLiteratura + DuraFrancesHistoria #= 34, 
    DuraFrancesHistoria #= 3, 

    % ingles 
    ComumInglesHistoria + ComumInglesLiteratura + DuraInglesHistoria + DuraInglesLiteratura #= 46,
    ComumInglesLiteratura + ComumInglesHistoria #= 23, 
    
    DuraFrancesLiteratura + ComumFrancesLiteratura  #= 20, 

    ComumFrancesLiteratura + ComumInglesLiteratura #= 31,
    labeling([], Variaveis), 
    sumlist(Variaveis, X), 
    write(X).
     

    


    