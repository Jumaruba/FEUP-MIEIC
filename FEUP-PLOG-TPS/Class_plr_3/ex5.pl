:-use_module(library(clpfd)). 


solve(Casal):- 
	
	Casal = [[J1,J2], [M1,M2]],  
	append(Casal, TarefasCasal), 
	
	domain(TarefasCasal, 1, 4), 
	all_distinct(TarefasCasal),
	
	TempoMaria = [45,78,36,29], 
	TempoJoao = [49,72,43,31], 
	element(M1, TempoMaria, TM1), 
	element(M2, TempoMaria, TM2),
	element(J1, TempoJoao, TJ1), 
	element(J2, TempoJoao, TJ2), 
	
	TempoTotal #= TM1 + TM2 + TJ1 + TJ2, 
	labeling([minimize(TempoTotal)], TarefasCasal). 