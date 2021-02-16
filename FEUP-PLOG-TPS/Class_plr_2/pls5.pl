:-use_module(library(clpfd)).
:-use_module(library(lists)). 

solve(Cores, Taman):-
    Cores = [Amar, Verd, Azul, Pret],  
    Taman = [Prim, Seg, Terc, Quart],   
    Total = [Amar, Verd, Azul, Pret, Prim, Seg, Terc, Quart], 
    domain(Total, 1, 4), 
    all_distinct(Cores), 
    all_distinct(Taman), 

    % Restricoes  
    PosBefore #= Azul-1, 
    PosAfter #= Azul+1, 
    nth1(AntesAzul, Taman, PosBefore),   
    nth1(DepoisAzul, Taman, PosAfter), 
    AntesAzul #< DepoisAzul, 

    Verd #= Prim, 
    Verd #> Azul,
    Amar #> Pret,  
    labeling([], Total). 
    
    
