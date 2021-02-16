passaro(tweety). 
peixe(goldie). 
minhoca(molie). 
amigo_de(eu, silvester).
gato(silvester).  

gosta_de(X, Y):- 
    passaro(X), 
    minhoca(Y). 

gosta_de(X,Y):- 
    gato(X), 
    peixe(Y). 

gosta_de(X,Y):- 
    gato(X), 
    passaro(Y). 

gosta_de(X,Y):- 
    amigo_de(X,Y). 

gosta_de(Y,X):- 
    amigo_de(Y,X). 

come(X, Y):- 
    gato(X), 
    gosta_de(X, Y). 


% come(silvester, X).