:-use_module(library(clpfd)). 

% OK 
% task(numero,votante, tempo, sofrimento). 


solve(N,Est):-   
    % estrategia 1 - 2U, +1F
    % estrategia 2 - 5U, +4F
    % estrategia 3 - 1U, -11F 
    Tasks = [1,2,1,
             3,5,4,
             -10,1,-11], 
             
    length(Est, N), 
    domain(Est, 0, 3), 
    evaluate(Est, Votos, Sof, Tempo, Tasks), 
    Tempo #=< 10, 
    Votos #= 5 #\/ Votos #= 6,
    labeling([minimize(Sof)], Est).  

evaluate([], 0, 0,0 , _). 
evaluate([X|Est], VotesTotal, SofrimentoTotal, TempoTotal, Tasks):-
    X_ #= X -1, 
    VotantePos #= X_*3 +1,
    TempoPos #= X_*3+2,
    SofrimentosPos #= X_*3+3,  
    
    element(VotantePos, Tasks, Votante), 
    element(TempoPos, Tasks,Tempo), 
    element(SofrimentosPos, Tasks, Sofrimento), 

    VotesTotal #= NewVotes + Votante,
    TempoTotal #= NewTempo + Tempo, 
    SofrimentoTotal #= Sofrimento + NewSofrimento,  
    evaluate(Est, NewVotes, NewSofrimento, NewTempo, Tasks). 



    



