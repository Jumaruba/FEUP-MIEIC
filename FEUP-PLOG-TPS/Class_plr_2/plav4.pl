:-use_module(library(clpfd)). 
:-use_module(library(lists)).   

    
solve(N, Seq):-
    length(Seq, N), 
    domain(Seq, 0, 10000),   

    nth1(1, Seq, First),
    First #= 0,   

    set_less(Seq),   
    differences(Seq, Diferencas, Seq), 
    append(Diferencas, Diff),
    all_distinct(Diff),     

    maximum(Max, Diff), 
    labeling([minimize(Max)], Seq), !. 


differences([],[], _). 
differences([X|L], [Diff|Diferencas], Seq):-
    difference(Seq, X, Diff), 
    differences(L, Diferencas, Seq). 

difference([X|Seq], X, []). 
difference([X], X, []). 
difference([X|Seq], Elem, [Diff|Diffs]):- 
    Elem - X #= Diff,
    difference(Seq, Elem, Diffs). 




set_less([_]).
set_less([X,Y|Seq]):- 
    X #< Y, 
    set_less([Y|Seq]). 


