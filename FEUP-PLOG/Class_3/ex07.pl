% Implementation of the before predicate 

before_(First, Sec, L):-
	append(_, [First|L2], L), 
	append(_, [Sec|_], L2). 

% consult('ex07.pl').
% before_(3,7,[1,2,3,4,5,6,7,8]).  
% before_(7,3,[1,2,3,4,5,6,7,8]). 
%

