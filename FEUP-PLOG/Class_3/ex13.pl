% a) Get all the elements between 1 and n 

lista_ate(N, [N|L]):-  
	N >=1,
	N1 is N-1, 
	lista_ate(N1, L). 

lista_ate(0, []).   

% b) Get between N1 and N2 including them. 

lista_entre(N2, N2, [N2]).  
lista_entre(N1, N2, [N1|L]):- 
	N_next is N1+1,  
	lista_entre(N_next, N2, L). 

% c) Build sum_list(L, Sum). 

sum_list([], 0). 
sum_list([X|L], Sum):- 
	sum_list(L, Sum_1), 
	Sum is X+Sum_1. 

% d) Find out if a number is even.  

even(X):- 0 is mod(X,2).  

% e) lista_pares(N, Lista). In order to train the language, I'll not use the previous functions. Also I'll give the restriction N >= 0. 

lista_pares(N, [N|L]):-  
	N >=0,  
	0 is mod(N,2), 
	N1 is N-1,
	lista_pares(N1, L). 
lista_pares(N, L):-
	N >= 0, 
	1 is mod(N,2), 
	N1 is N-1, 
	lista_pares(N1,L). 

lista_pares(0,[0]). 
	
% f) lista_impares(N, Lista). Same condition of the problem above.  

lista_impares(N, [N|L]):-
	N >= 1, 
	1 is mod(N, 2), 
	N1 is N-1, 
	lista_impares(N1, L).

lista_impares(N, L):-
	N >= 1,  
	N1 is N-1, 
	0 is mod(N,2), 
	lista_impares(N1, L). 

lista_impares(1, [1]).  


% consult('ex13.pl').  
% lista_ate(11, L). 
% lista_entre(4,10,L). 
% sum_list([1,2,3,4], N). 
% even(100). 

	
