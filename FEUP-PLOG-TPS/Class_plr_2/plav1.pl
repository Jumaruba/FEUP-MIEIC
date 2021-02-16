:-use_module(library(clpfd)). 

solve(N, Seq):-   
    % seq de tamanho N 
    length(Seq, N),
    % 0 1 2
    % 2 0 1
    N_ is N -1, 
domain(Seq, 0, N_),
    set_times(N, Seq, 0, Seq),  
    labeling([], Seq). 


exactly([], X, 0). 
exactly([X|Seq], Num, Exp):-
    X #= Num #<=> B, 
    Exp #= B + NewExp,
    exactly(Seq, Num, NewExp).  

set_times(N, [], N, Seq). 
set_times(N, [X|L], Acc, Seq):-    
    exactly(Seq, X, Acc), 
    NewAcc is Acc+1, 
    set_times(N, L, NewAcc, Seq). 

    

    
    

