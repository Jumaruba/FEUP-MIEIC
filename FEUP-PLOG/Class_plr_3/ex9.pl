:-use_module(library(clpfd)). 

% DEMORA ANOS  

solve(Fabrica, Lucro, Tempo1, Tempo2):-

    domain([Tempo1, Tempo2], 1 ,700),
    domain([Fabrica], 1, 2),


    element(Fabrica, [50,40], LucroHora1), 
    element(Fabrica, [40,25], LucroHora2), 
    element(Fabrica, [500,700], TotalHoras), 


    TotalHoras #= Tempo1 + Tempo2, 
    Lucro1 #= Tempo1*LucroHora1*10, 
    Lucro2 #= Tempo2*LucroHora2*15, 
    Lucro #= -130000 + Lucro1 + Lucro2, 

    labeling([maximize(Lucro)], [Fabrica, Tempo1, Tempo2]).

