:-use_module(library(clpfd)).
:-use_module(library(lists)). 

solve(Nacionalidade, LaVie, Sistema, Fagor):-
    Nacionalidade = [Ale, Ing, Bra, Esp, Ita, Fra], 
    LaVie = [L1, L2], 
    Sistema = [S1, S2], 
    Fagor = [F1, F2],  
    append([LaVie, Sistema, Fagor], Marcas), 
    append([Marcas, Nacionalidade], Total), 
    domain(Nacionalidade, 1, 6), 
    all_distinct(Marcas), 
    all_distinct(Nacionalidade),

    Ale #= L2, 
    L1 #= 1, 

    Bra #= S2, 
    S1 #= 5, 

    Esp #= F2, 
    3 #= F1, 

    Esp #\= 2, 
    Esp #\= 6, 

    Ita #\= 3, 
    Fra #\= 3,
    
    Ale #\= 2, 
    Ita #\= 1, 

    labeling([], Total). 
    


    
    
    