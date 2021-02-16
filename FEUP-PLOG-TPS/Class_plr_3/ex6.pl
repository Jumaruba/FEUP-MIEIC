:-use_module(library(clpfd)). 

solve(N, Investimentos):-
    Lucro = [17, 10 ,15 ,19, 7 ,13,9],
    Capital = [43,28,34,48,17,32,23],
    length(Investimentos, N), 
    domain(Investimentos, 1, 7), 
    all_distinct(Investimentos),
    lucroTotal(Investimentos, Lucro, Capital, LucroTotal), 
    labeling([maximize(LucroTotal)], Investimentos).

lucroTotal([], _,_,0):- !. 
lucroTotal([X|Investimentos], Lucro, Capital, LucroTotal):-
    element(X, Lucro, LucroElem), 
    element(X, Capital, CapitalElem), 
    CurrLucro #= LucroElem - CapitalElem, 
    LucroTotal #= CurrLucro + OtherLucro, 
    lucroTotal(Investimentos, Lucro, Capital, OtherLucro). 

