:-use_module(library(clpfd)). 
:-use_module(library(lists)).

solve(Matrix):- 
    
    create_matrix(Matrix, 8),
    append(Matrix, Total),   
    domain(Total, 0, 31), 

    nvalue(32, Total), 
    nth0(0, Total, First),  
    First #= 0, 

    length(Total, TotalSize),  
    nth1(TotalSize, Total, Last),
    Last #= 0,    

    restrict(Matrix, 2, Matrix), 
    labeling([], Total).



create_matrix([], 0). 
create_matrix([Line|Matrix], Acc):-    
    length(Line, 8), 
    NewAcc is Acc -1, 
    create_matrix(Matrix, NewAcc).  

    
restrict([_,_], _, _). 
restrict([F,X,L|M], Line, Matrix):-  
    restrictLines(X, Line, 2, Matrix),  
    NewLinePos is Line +1, 
    restrict([X,L|M], NewLinePos, Matrix). 
    

    

restrictLines([_,_], _, _, _). 
restrictLines([Prev,Elem, Next|Line], PosLine, PosCol, Matriz):-    
    PrevLinePos is PosLine - 1 ,
    NextLinePos is PosLine +1, 
    nth1(PrevLinePos, Matriz, PrevLine),  
    nth1(PosCol, PrevLine, PrevLineElem), 

    nth1(NextLinePos, Matriz, NextLine),  
    nth1(PosCol, NextLine, NextLineElem), 

    Elem #= Prev #\/ 
    Elem #= Next #\/ 
    Elem #= PrevLineElem #\/ 
    Elem #= NextLineElem, 

    NewPosCol is PosCol+1, 
    restrictLines([Elem,Next|Line], PosLine, NewPosCol, Matriz).  

