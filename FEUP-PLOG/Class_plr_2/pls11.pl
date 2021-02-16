:-use_module(library(clpfd)).
:-use_module(library(lists)).
solve(Pessoas, Esporte):-
    Pessoas = [Claudio, David, Domingos, Francisco, Marcelo, Paulo], 
    Esporte = [Pin, Fut, And, Rug, Ten, Vol],  
    append([Pessoas, Esporte], Total), 
    all_distinct(Pessoas), 
    all_distinct(Esporte), 
    domain(Total, 1, 6), 

    Marcelo #= Futebol, 
    David #= Tenis, 
    all_distinct([Francisco, Paulo, Vol]), 
    Domingos #\= Rug,  
    Domingos #\= And, 

    all_distinct([Claudio, Francisco, And, Rug]),  
    labeling([], Total). 

    

    
