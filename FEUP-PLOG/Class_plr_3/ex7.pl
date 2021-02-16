:-use_module(library(clpfd)). 
:-use_module(library(lists)). 


solve(Camioes):- 
	A is 1, B is 2, C is 3, D is 4, E is 5, F is 6, G is 7, H is 8, I is 9, 
    
    Tempo = [6,4,7,5,4,6,5,3,7,6], 
    Camioes = [C1, C2, C3], 
	Caminhos = [Caminho1, Caminho2, Caminho3], 
	length(Caminho1, 3), length(Caminho2, 3), length(Caminho3, 3), 
	append([Caminho1, Caminho2, Caminho3], TodosCaminhos),
	domain(TodosCaminhos, 1,9),
    domain(Camioes, 1, 10), 
	
	all_distinct(TodosCaminhos), 
	all_distinct(Camioes), 
	
    Percursos = [A,D,G,
				 F,B,I,
				 H,E,C,
				 B,E,C,
				 A,F,H,
				 D,B,E,
				 G,I,C,
				 D,G,F,
				 A,B,C,
				 I,B,H], 
	
	get_caminho(Percursos, C1, Caminho1), 
	get_caminho(Percursos, C2, Caminho2), 
	get_caminho(Percursos, C3, Caminho3), 
	
	tempo_total(Camioes, Tempo, TempoTotal), 
	
	labeling([minimize(TempoTotal)], Camioes). 
	
get_caminho(Percursos, Index, Caminho):- 
	Pos1 #= (Index-1)*3 +1, 
	Pos2 #= (Index-1)*3 +2, 
	Pos3 #= (Index-1)*3 +3, 
	element(Pos1, Percursos, Ca1), 
	element(Pos2, Percursos, Ca2), 
	element(Pos3, Percursos, Ca3), 
	Caminho = [Ca1, Ca2, Ca3]. 


tempo_total([C1,C2,C3], Tempo, TempoTotal):-
	element(C1, Tempo, T1), 
	element(C2, Tempo, T2), 
	element(C3, Tempo, T3), 
	
	TempoTotal #= T1 + T2 + T3. 
	
				 