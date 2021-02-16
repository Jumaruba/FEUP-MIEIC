:-use_module(library(clpfd)). 

solve(Total):-
    Total = [Joao, Antonio, Francisco, Harpa, Violino, Piano, Terca, Quinta1, Quinta2], 
    Pessoas = [Joao, Antonio, Francisco], 
    Instrumento = [Harpa, Violino, Piano],       
    Ensaio = [Terca, Quinta1, Quinta2],  
    domain(Total, 1,3),  
    all_distinct(Pessoas),
    all_distinct(Instrumento),
    all_distinct(Ensaio), 
    Antonio #\= Piano,   
    Piano #= Terca, 
    Joao #\= Violino,  
    Joao #\= Piano,    
    Joao #= Quinta1, 
    Violino #= Quinta2, 
    labeling([], Total). 



