:-use_module(library(clpfd)). 

% OK 
solve(Casas):-
     Casas = [C1,C2,C3,C4,C5,C6,C7,C8,C9],
     domain(Casas, 1, 9), 
     all_distinct(Casas),
     C9 #= 6,  
    diferences(Casas, Total),  
    labeling([maximize(Total)], Casas). 


diferences([_], 0). 
diferences([C1,C2|Casas], Total):-  
    abs(C1-C2) #= Total_, 
    Total #= Total_ + OtherTotal, 
    diferences([C2|Casas], OtherTotal). 