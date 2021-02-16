:-use_module(library(clpfd)).  
:-use_module(library(lists)). 

luzes(Estado):- 
    % aceso 1, apagado 0 
    length(Estado, Side),
    Tamanho is Side*Side, 
    somaMatriz(Estado, Soma), 
    Soma #= Tamanho, 
    
    


somaMatriz([], 0). 
somaMatriz([X|Estado], Acc):-     
    sum(X, #=, Soma),   
    somaMatriz(Estado, OtherSum), 
    Acc #= Soma + OtherSum. 




