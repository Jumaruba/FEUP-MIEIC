:-use_module(library(clpfd)). 
:-use_module(library(lists)). 


% Caso de estudo de equivalencia para predicados em forma de lista. 
solve(Tasks, TotalTime, Time):-
    FirstDelay = [4,5,8,9,4], 

    % Predicados com o primeiro elemento equivalente a linha. 
    Delays = [0,7,12,10,9,
              6,0,10,14,11,
              10,11,0,12,10,
              7,8,15,0,7,
              12,9,8,16,0], 

    length(Tasks, 5), 
    domain(Tasks,1,5),
    all_distinct(Tasks),
    get_total_time(Tasks, Delays, Time), 

    element(1, Tasks, First),
    element(First, FirstDelay, FirstTime), 
    TotalTime #= FirstTime + Time, 
    append([Tasks, [TotalTime]], Total),
    labeling([minimize(TotalTime)], Total). 


get_total_time([_], _, 0).
get_total_time([X,Y|Tasks], Delays, TotalTime):-
    % Como aceder ao elemento.
    X_ #= X -1, 
    Pos #= X_*5 + Y, 
    
    element(Pos, Delays, Time),
    TotalTime #= Time + OtherTime, 
    get_total_time([Y|Tasks], Delays, OtherTime). 

