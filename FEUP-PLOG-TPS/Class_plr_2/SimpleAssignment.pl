:-use_module(library(clpfd)).

solve(Workers):-
    Workers = [W1,W2,W3,W4],  
    
    domain(Workers,1,4), 
    all_distinct([W1,W2,W3,W4]),  

    % it makes difference using variables in the place of the lists. 
    element(W1, [7,1,3,4], P1), 
    element(W2, [8,2,5,1], P2), 
    element(W3, [4,3,7,2], P3),
    element(W4, [3,1,6,3], P4), 

    P1 + P2 + P3 + P4 #>= 19,  
    
    % if we wanna maximize:
    maximize(labeling([ff], Workers)).