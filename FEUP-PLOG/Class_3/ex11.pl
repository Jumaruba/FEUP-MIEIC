% achata lista 

achata_lista([X|L], [X|L1]):-   
	atomic(X),
	achata_lista(L,L1). 

achata_lista([X|L], L1):- 
	\+atomic(X),  
	append(X, L, Z),
	achata_lista(Z, L1). 

achata_lista([], []).  

% consult('ex11.pl').
% achata_lista([1,2,[3,4],[[6]]], L).

