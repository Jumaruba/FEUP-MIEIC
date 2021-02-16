:-use_module(library(clpfd)). 

solve(Children):- 
    Children = [A,B,C],   
    domain(Children,1,10),
    36*A + 32*B + 16*C #= 0,
    abs(A - B) #> 2, 
    abs(B - C) #> 2, 
    abs(C - A) #> 2, 
    labeling([ff], Children). 



