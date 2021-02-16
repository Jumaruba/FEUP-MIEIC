:-use_module(library(clpfd)). 


solve:-
    length(Jogadores, 32),  
    domain(Jogadores, 1,32),
    all_distinct(Jogadores),  

    set_pairs(Jogadores, Jogadores, Matrix), 
    append(Matrix, Relation), 
    all_distinct(Relation), 

    labeling([], Partidas),
    length(Partidas).


set_pairs([], _, []).
set_pairs([P|J], Players, [Relations|Matrix]):-
    set_pair_player(P, Players, Relations), 
    set_pairs(J, PLayers, Matrix). 

set_pair_player(P, [P|J], []):- !. 
set_pair_player(Player, [P|J], [Player-P|Relation]):- 
    set_pair_player(Player, J, Relation). 

    