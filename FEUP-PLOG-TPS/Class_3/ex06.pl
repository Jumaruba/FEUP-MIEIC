% a) delete one elemetn of the list 

delete_one(X, L1, L2):- 
	append(K1, [X|K2], L1), 
	append(K1, K2, L2). 

%b) delete all 

delete_all(X, [], []). 
delete_all(X, [X| L1], Ans) :- 
	delete_all(X, L1, Ans).  

delete_all(X, [Y|L1], [Y|Ans]):-  
	X \= Y, 
	delete_all(X, L1, Ans).  


%c) remove all the ocurrences from one list in another. 


delete_all_list(LX, [X|L1], [X|Ans]):-
	\+ member(X, LX), 
	delete_all_list(LX, L1, Ans). 

delete_all_list(LX, [X|L1], Ans):-
	member(X, LX),
	delete_all_list(LX, L1, Ans). 

delete_all_list(LX, [], []).  

% consult('ex06.pl'). 
% delete_all_list([1,2,3], [1,2,4,6,3,2], L). 
% L = [4,6] ? 



