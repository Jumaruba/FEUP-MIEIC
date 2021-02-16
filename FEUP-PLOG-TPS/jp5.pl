
inicial(0-0).
final(2-Y).

% esvazia 
action(L4_-L3_, 'esvazia L4', 0-L3_).
action(L4_-L3_, 'esvazia L3', L4_-0).

% fill 
action(L4_-L3_, 'enche L4', 4-L3_).
action(L4_-L3_, 'enche L3', L4_-3). 

% fill L3 
action(L4_-L3_, 'enche L4 de L3', L4-L3):- 
        Aux is L4_+L3_, 
        L4 is min(4, Aux),  
        L3 is L3_ - L4 + L4_.

% fill L4 
action(L4_-L3_, 'enche L3 de L4', L4-L3):-
        Aux is L4_ + L3_,
        L3 is min(3, Aux), 
        L4 is L4_ - L3 + L3_.

dfs(P):-
        inicial(I), 
        final(F), 
        dfs(I, F, [], P). 

dfs(F, F, _, []). 

dfs(I, F, V, [NP|P]):-  
        \+member(I, V), 
        action(I, NP, C), 
        dfs(C, F, [I|V], P).
