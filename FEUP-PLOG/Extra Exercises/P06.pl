/* 
 Find out whether a list is a palindrome.
 A palindrome can be read forward or backward; e.g. [x,a,m,a,x].
*/ 

% Our strategy is to reverse the list and check if it's equals 

reverse_aux([], Ys, Ys). 
reverse_aux([X|Xs], Ys, Zs):- 
	reverse_aux(Xs, [X|Ys], Zs). 
	
reverse(Xs, Zs):- 
	reverse_aux(Xs, [], Zs). 
	

check_palindrome(Xs):- 
	reverse(Xs, Ys), 
	Xs == Ys.

% or we can do something like 

check_palindrome_(Xs):-
	reverse(Xs, Xs). 