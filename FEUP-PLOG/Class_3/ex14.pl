% a) prime(N). 

prime(N):-  
	N1 is sqrt(N), 	% Stop at the squared root. 
	prime(N, 2). 

prime(N, Acc):- 
	Acc < N, 				% Stop condition. 
	\+ 0 is mod(N, Acc), 	
	Acc1 is Acc+1, 
	prime(N, Acc1). 

prime(N,N1):-
	N1 >=N. 	
prime(2). 

% b) lista_primos(N). 

lista_primos(N, [N|L]):- 
	N >2, 
	prime(N), 
	N1 is N -1,  
	lista_primos(N1, L). 

lista_primos(N, L):-
	N > 2, 
	\+ prime(N),  
	N1 is N-1, 
	lista_primos(N1,L).  	

lista_primos(2, [2]). 
% consult('ex14.pl'). 
