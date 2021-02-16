:-use_module(library(clpfd)). 
:-use_module(library(lists)). 

solve(Corp, X):-   
    Corp = [A, B, C, AB, AC, BC, X], 
    domain(Corp, 1,200),   

    A + B + C + AB + AC + BC #= 170,   
    A + AB + AC #= 100,
    B + AB + BC #= 105,  
    C + AC + BC #= 35, 
    X #= A + B + C, 
    labeling([], Corp). 

    


