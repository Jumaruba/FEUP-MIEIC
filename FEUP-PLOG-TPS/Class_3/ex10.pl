% a) Finds out if the list is ordenated 

ordenada([X,Y|L1]):- 
	Y >= X, 
	ordenada([Y|L1]). 
ordenada([X]).  

% ordenada([1,2,3,4,5]). 
% ordenada([1,2,3,2]). 


% a) Ordenates the a list.   

% Inneficient way using permutation -----------------------------------------

/* Gets one element from the array and delete it*/ 
 select(X, [Y|Xs], [Y|Zs]):- 
	 X \== Y, 
	 select(X, Xs, Zs).  
 select(X, [X|Xs], Xs). 

permutation(L1, [X|L2]):-    
	select(X, L1, K), 
  	permutation(K, L2). 

permutation([], []).   

stupid_sort(L1, L2):-
	permutation(L1, L2),
	ordenada(L2). 

% Insertion sort ------------------------------------------------------------  
insertion_sort(L1, L2):- 
	insertion_sort(L1, L2, []). 

insertion_sort(L1, L2, Acc):-
	find_max(L1, Max), 
	delete_val(Max, L1, New_L1), 
	insertion_sort(New_L1, L2, [Max|Acc]).  

insertion_sort([], L2, L2). 



find_max([X|L1], Y):-   
	find_max(L1,K),
	max(X,K,Y). 

find_max([X],X). 

max(X, Y, Z):-
	X =< Y,
	Z is Y. 
max(X, Y, Z):-
	X > Y,
	Z is X. 
 
delete_val(X, L1, Ans):-
	append(L2, [X|L3], L1),
	append(L2, L3, Ans). 




% consult('ex10.pl').  


