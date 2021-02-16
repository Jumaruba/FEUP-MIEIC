:-use_module(library(clpfd)).
:-use_module(library(lists)). 

solve(Variaveis):- 
    Variaveis = [Interrogadas, LiquidoPo, None, Liquido, Po], 

    domain(Variaveis, 0,1000), 
    Interrogadas #= LiquidoPo + None + Liquido + Po, 
    Interrogadas #= 3*(Interrogadas - LiquidoPo - Po),
    2*Interrogadas #= 7*(Interrogadas - LiquidoPo - Liquido), 
    LiquidoPo #= 427,
    Interrogadas #= 5*None,

    labeling([], Variaveis). 

    

