pilot(lamb).
pilot(besenyei).
pilot(chambliss).
pilot(maclean). 
pilot(mangold).
pilot(jones). 
pilot(bonhomme).  

team(lamb, breitling). 
team(besenyei, redbull). 
team(chambliss, redbull).
team(maclean, maditerranea_racing).
team(mangold, cobra).
team(jones, matador).
team(bonhomme, matador).

plane(lamb, mx2).
plane(besenyei, edge540).
plane(chambliss, edge540).
plane(maclean, edge540).
plane(mangold, edge540).
plane(jones, edge540). 
plane(bonhomme, edge540). 

circuit(instanbul).
circuit(budapest).
circuit(porto).

win(jones, porto).
win(mangold, budapest).
win(mangold, instanbul).

gates(instanbul, 9).
gates(budapest, 6).
gates(porto, 5).


/*
a) win(X, porto).

b) win(X, porto), team(X, Y). 

c) win(X, Y), win(X, Z), Z@<Y.  

d) gates(X, Y), Y>8. 

e) plane(X, Y), Y\='edge540'. 
*/
/* 

Alguns conceitos da aula prática: 

    predicato - conjunto de regras e factos de um functor.  
    functor - ex. father/2. É basicamente uma função.  
    terms - em prolog tudo são termos: constantes, inteiros,  floats, átomos. 
            Átomos, são palavras que começam com letra minuscula ou entre aspas.  
    variáveis - começam com letra maiúscula, underscore ou são apenas underscore.  

*/



