comida(peru).  
comida(frango). 
comida(salmao).
comida(solha). 

bebida(cerveja).  
bebida(vinho_verde).   
bebida(vinho_maduro). 

female(ana). 
female(barbara). 

male(bruno). 
male(antonio). 

casado(bruno, antonio).
casado(ana, barbara). 

%primeiro é sempre bebida, o segundo é comida
combina(vinho_maduro, salmao).
combina(vinho_maduro, peru).
combina(vinho_verde, solha). 
combina(vinho_verde, salmao). 

gosta(barbara, peru). 
gosta(barbara, salmao).
gosta(barbara, frango). 
gosta(barbara, solha)- 

gosta(antonio, peru). 
gosta(antonio, salmao). 

gosta(bruno, solha). 

/*  
a) casado(ana, bruno), gosta(ana, vinho_verde), gosta(bruno, vinho_verde). 

b) combina(X, salmao). 

c) combina(vinho_verde, X). 

*/ 
