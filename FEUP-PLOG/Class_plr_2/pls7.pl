:- use_module(library(clpfd)). 

solve(Amigos, Bebida):- 
    Amigos = [Joao, Miguel, Nadia, Silvia, Afonso, Cristina, Geraldo, Julio, Maria, Maximo, Manuel, Ivone],
    Bebida = [Limonada, Guarana, Whisky, Vinho, Champ, Agua, Laran, Cafe, Cha, Ver, Cerv, Vodka], 
    Total = [Joao, Miguel, Nadia, Silvia, Afonso, Cristina, Geraldo, Julio, Maria, Maximo, Manuel, Ivone, Limonada, Guarana, Whisky, Vinho, Champ, Agua, Laran, Cafe, Cha, Ver, Cerv, Vodka],
    domain(Total, 1,12), 
       
    all_distinct(Amigos),
    all_distinct(Bebida),
    
    all_distinct([Geraldo, Julio, Vodka, Cerv, Ver, Cha, Maria, Maximo, Ivone, Manuel, Cafe, Laran]), 
    all_distinct([Joao, Miguel, Cha, Cafe, Julio, Geraldo, Guarana, Whisky, Nadia, Maria, Laran, Limonada]),  
    all_distinct([Geraldo, Agua, Maximo, Whisky, Joao, Silvia, Cha, Vodka]), 
    all_distinct([Julio, Agua, Champ, Miguel, Guarana, Vodka, Maximo, Manuel, Cafe, Silvia, Afonso]), 
    labeling([], Total).
    
    
    

    



