lingua(maias, portugues). 
lingua(sapies, ingles). 

tipo(maias, romance).   
tipo(sapies, cientifico). 

nacionalidade('eca de queiroz', portugues).  
nacionalidade('Yuval noah harari', israelense). 

livro(maias).   
livro(sapiens). 

escreveu('Yuval noah harari', sapiens). 
escreveu('Eca de Queiroz', maias). 

/*
queries 

a) 
escreveu(X, maias). 

b) 
tipo(X, romance), escreveu(Y, X). 

c) 
tipo(X, ficcao), escreveu(Y,X), escreveu(Z, X), Z@<Y. 

*/ 