:-use_module(library(clpfd)). 



solve():- 

    QuantA #= 3*QuantA1*TempoA1 + 2*QuantA2*TempoA2, 
    Lucro #= QuantA * 16, 

    QuantB #= 