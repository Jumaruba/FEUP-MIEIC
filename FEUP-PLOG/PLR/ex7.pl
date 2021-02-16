%ex7) 

peru(Vars, Price):- 
	Vars = [P1, P4], 
	domain(Vars, 1,9),
	P1 * 1000 + P4 + 670 #=  S,
	S mod 72 #= 0,
	labeling([], Vars),
	Price is S//72. 