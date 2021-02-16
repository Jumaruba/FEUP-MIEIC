:-use_module(library(clpfd)). 
:-use_module(library(between)).

objeto(piano,3,30). 
objeto(cadeira, 1,10).
objeto(cama, 3, 15). 
objeto(mesa, 2,15). 
homens(4). 
tempo_max(60).



furniture:-
	tempo_max(TempoMax), 
	homens(Homens),
	TwiceTempMax is TempoMax *2, 
	findall(Name, objeto(Name, _,_), Objects),  
	length(Objects, Size), 
	length(Ss, Size), 
	length(Es, Size), 
	domain(Ss, 1, TempoMax), 
	domain(Es, 1, TwiceTempMax),
	
	
	generate_tasks(Ss, Es, 1, Tasks, Objects), 
	

	cumulative(Tasks, [limit(Homens)]), 
	append([Ss, Es], Variables), 
	labeling([minimize(TempoMax)], Variables),
	write(Ss), nl, 
	write(Es), nl,
	write(Tasks).
	
generate_tasks([],[],_,[],[]). 
generate_tasks([S|Ss], [E|Ee], Ti, [task(S,Di,E,Hi,Ti)|Tasks], [Name|Objects]):- 
	objeto(Name, Hi, Di), 
	New_Ti is Ti +1, 
	generate_tasks(Ss, Ee, New_Ti, Tasks, Objects). 
	
	