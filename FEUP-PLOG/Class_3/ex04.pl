% Invert a list 

inverter_([], L2, L2).   

inverter_(L1, L2):-  
	inverter_(L1, L2, []).  

inverter_([X|L1], L2, L):- 
	inverter_(L1, L2, [X|L]). 
	

