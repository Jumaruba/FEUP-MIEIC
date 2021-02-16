:-use_module(library(clpfd)). 

% 56 cartas 
% / 13 = 0, vermelho coracao
% / 13 = 1, vermlho losango 
% / 13 = 2, preto trevo 
% / 13 = 3, preto coisa 


solve(Hand):- 

    create_hand(Hand, 5), 
    append(Hand, Total),
    all_distinct(Total),
    domain(1, 53), 

    get_pontuation(Hand, Pont1), 
    transpose(Hand, Transposed), 
    get_pontuation(Transposed, Pont2), 
    Points #= Pont1 + Pont2, 
    labeling([maximize(Points)], Total). 
    

    


create_hand([], 0). 
create_hand([Line|Hand], Size):- 
    length(Line, 5),  
    NewSize is Size -1,  
    create_hand(Hand, NewSize).  

get_pontuation([], 0). 
get_pontuation([Line|Matrix], TotalPont):-
    pontuation(Line, Point), 
    TotalPont #= Point + NewPoint, 
    get_pontuation(Matrix, NewPoint). 

pontuation([C1,C2,C3,C4], 400):- 
    C1 #= 1, C2 #= 14, C3 #= 27, C4 #= 40, !.
pontuation([C1,C2,C3,C4], 300):-
    C





