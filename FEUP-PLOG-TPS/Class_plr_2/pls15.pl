:-use_module(library(clpfd)).
:-use_module(library(lists)). 

solve:- 
    Nome = [Paula, Artur, Daniel, Ema], 
    Sobrenome = [Mala, Postal, Bola, Famoso], 
    Endereco = [Espanha, Turquia, Primavera, Hungria, Sardenha], 
    Encomenda = [Roupa, Catalogo, Plantas, Livro],

    all_distinct(Nome),
    all_distinct(Sobrenome),
    all_distinct(Endereco),
    all_distinct(Encomenda),

    Mala #= Crianca, 

    Paula #= Postal,
    Bola #\= Espanha, 
    all_distinct(Paula, Bola, Artur, Catalogo), 

    Turquia #\= Plantas, 

    Ema #= Primvaera, 

    Paula #\= Hungria, 
    Bola #\= Hungria, 
    Hungria #\= Livro, 

    Plantas #\= Famoso, 
    Famoso #= Sardenha, 
    Famoso #\= Daniel. 

    

