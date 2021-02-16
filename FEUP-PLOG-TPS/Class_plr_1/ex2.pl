:-use_module(library(clpfd)). 

% Como armazenar a resposta? 
% Pela posição da casa. 
zebra(Zebra, Agua):-
	CoresCasas = [Verm, Amar, Azul, Verde, Branca], 
	Nacionalidade = [Ing, Esp, Nor, Ucr, Pt],
	Bebida = [Laranja, Cha, Cafe, Leite, Agua],
	Cigarro = [Marlboro, Chester, Winston, Luky, SG],
	Animal = [Cao, Raposa, Iguana, Cavalo, Zebra], 
	
	List = [Verm, Amar, Azul, Verde, Branca,Ing, Esp, Nor, Ucr, Pt, 
		Laranja, Cha, Cafe, Leite, Agua, Marlboro, Chester, Winston, Luky, SG, Cao, Raposa, Iguana, Cavalo, Zebra], 

	domain(List, 1, 5), 
	all_distinct(CoresCasas), 
	all_distinct(Nacionalidade), 
	all_distinct(Bebida),
	all_distinct(Cigarro),
	all_distinct(Animal),   
	
	Ing #= Verm, 
	Esp #= Cao,  
	Nor #= 1, 
	Amar #= Marlboro, 
	abs(Chester-Raposa) #=1, 
	abs(Nor-Azul) #= 1,  
	Winston #= Iguana, 
	Luky #= Laranja, 
	Ucr #= Cha, 
	Pt #= SG,  
	abs(Marlboro-Cavalo) #= 1, 
	Verde #= Cafe, 
	(Verde-Branca) #= 1,  
	Leite #= 3, 

	labeling([],List).


	

