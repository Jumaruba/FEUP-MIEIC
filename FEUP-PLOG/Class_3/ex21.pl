


slice(Lista, Ind1, Ind2, Result):- 
	slice(Lista, 1, Ind1, Ind2, Result). 

slice([X|L], Acc, Ind1, Ind2, [X|R]):- 
	Acc >= Ind1, 
	Acc =< Ind2, 
	Acc1 is Acc +1, 
	slice(L, Acc1, Ind1, Ind2, R). 


slice([X|L], Acc, Ind1, Ind2, R):- 
	(Acc < Ind1; Acc > Ind2), 
	Acc1 is Acc+1, 
	slice(L, Acc1, Ind1, Ind2, R).  

slice([], Acc, Ind1, Ind2, []). 
