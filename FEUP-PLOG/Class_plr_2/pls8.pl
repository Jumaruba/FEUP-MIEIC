:-use_module(library(clpfd)).
:-use_module(library(lists)).
solve_pls8(Pessoas, Comida):-
    Pessoas = [Bernard, Daniel, Francisco, Henrique, Jaqueline, Luis], 
    Comida = [Peixe, Porco, Pato, Omelete, Bife, Espar],      
    append([Pessoas, Comida], Total), 
    domain(Total, 1, 6), 
    all_distinct(Pessoas),
    all_distinct(Comida),
    
    Daniel #\= Peixe, 
    Jaqueline #\= Peixe, 

    Francisco #\= Porco, 
    Francisco #\= Pato, 

    all_distinct([Bernard, Daniel, Omelete, Pato]),  
    Bernard #= Pato #\/ Bernard #= Porco #\/ Bernard #= Bife,  
    Francisco#= Pato #\/ Francisco#= Porco #\/ Francisco#= Bife, 
    Henrique#= Pato #\/ Henrique#= Porco #\/ Henrique#= Bife,  

    labeling([], Total).

    




    

