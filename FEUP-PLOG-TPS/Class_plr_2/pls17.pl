:-use_module(library(clpfd)). 
:-use_module(library(lists)). 

solve(Carros):-
    % 1 - Amarelo 
    % 2 - Verde 
    % 3- Vermelho 
    % 4- Azul 
    length(Carros, 12),
    global_cardinality(Carros, [1-4, 2-2, 3-3, 4-3]), 

    nth1(1, Carros, PrimCar), 
    nth1(12, Carros, UltimoCar), 
    PrimCar #= UltimoCar, 

    nth1(2, Carros, SegCar), 
    nth1(11, Carros, PenCar), 
    SegCar #= PenCar, 

    nth1(5,Carros, QuintoCar), 
    QuintoCar #= 4  , 

    consecutivos_distintos(Carros), 

    only_sec(Carros, 1), 

    labeling([], Carros),
    write(Carros). 


consecutivos_distintos([Car1, Car2]). 
consecutivos_distintos([Car1, Car2, Car3|L]):-
    all_distinct([Car1, Car2, Car3]), 
    consecutivos_distintos([Car2, Car3|L]). 

only_sec([_,_,_], 0). 
only_sec([X,Y,Z,W|L], Count):-
    (X#= 1 #/\ Y#= 2 #/\ Z#= 3 #/\ W#=4) #<=> B,
    Count #= B + NewCount, 
    only_sec([Y,Z,W|L], NewCount).  




    

