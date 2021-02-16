:-use_module(library(clpfd)).
:-use_module(library(lists)). 

solve_pls9(Pessoas):-
    Pessoas = [Carlos, Ricardo, Raul, Tomas, Roberto, Boris, Diego, Luis], 
    
    domain(Pessoas, 1, 8),  
    all_distinct(Pessoas),
    
    Boris #\= 7, 
    Tomas #=< 4, 
    
    Raul #\= 4,
    Tomas #\= 4, 

    Diego #\= 7,
    Boris #\= 8,   

    Roberto #\= 5,  
    Raul #\= 5, 

    Carlos #= 1 #\/ Carlos #=2, 
    Luis #= 2 #\/ Luis #= 1, 


    all_distinct([7, Luis, Ricardo, Boris, 3, 1,4,5]), 
    labeling([], Pessoas). 

