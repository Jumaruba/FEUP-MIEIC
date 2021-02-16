:- use_module(library(clpfd)). 
:- use_module(library(clpfd)). 
solve(Pessoas, Artigo, Andar):-  
    Total = [Adams, Baker, Catt, Dodge, Ennis, Fisk, Livro, Vestido, Bolsa, Gravata, Chapeu, Cand, Terr, Seg1, Seg2, Terc, Quin, Sex], 
    Pessoas = [Adams, Baker, Catt, Dodge, Ennis, Fisk],
    Artigo = [Livro, Vestido, Bolsa, Gravata, Chapeu, Cand],  
    Andar = [Terr, Seg1, Seg2, Terc, Quin, Sex],  
    domain(Total, 1, 6), 
    all_distinct(Pessoas),
    all_distinct(Artigo), 
    all_distinct(Andar),    

    Adams #= Livro,
    Livro #= Terr,  

    % 3  
    Catt #= Seg1, 
    Gravata #= Seg2,    
    % 4 
    Terc #= Vestido,  
    % 5 
    Cand #= Quin, 
    Fisk #= Sex,  
    % 6 
    Bolsa #= Seg1 #\/ Bolsa #= Seg2,  
    Baker #\= Bolsa, 
    Baker #\= Gravata,  
    Ennis #= Cand,   
    labeling([], Total). 

    




