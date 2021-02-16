:-use_module(library(clpfd)). 


solve(Variaveis):-
    Variaveis = [WakeUp, TakeBus, StartWork, TakeBus2,
    TurnTVOn, FallASleep],  

    domain(Variaveis, 1,24),  
    WakeUp #> 6,  
    WakeUp  #< TakeBus -1, 
    StartWork #>= TakeBus +1, 
    TakeBus2 #>= StartWork + 8, 
    TakeBus2 + 1 #=< TurnTVOn, 
    FallASleep - 3 #>= TurnTVOn,  

    labeling([], Variaveis). 



    
