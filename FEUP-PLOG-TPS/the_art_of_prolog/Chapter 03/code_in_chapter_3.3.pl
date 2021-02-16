% 3.18 delete all occurrences in a list of an element. 

delete_([X|Ls], X, Zs):- 
        delete_(Ls, X, Zs).

% case the element L is not X. If statment!
delete_([L|Ls], X, [L|Zs]):- 
        L =\= X, 
        delete_(Ls, X, Zs). 

delete_([], X, []). 

 % 3.19 delete just one occurrence of X 

select_([X|Ls], X, Ls). 
select_([L|Ls], X, [L|Zs]):- 
        L \== X, 
        select_(Ls, X, Zs).
 
 
% Check if a list is ordered.  

ordered_([X]). 
ordered_([]). 
ordered_([X,Y|Xs]):- 
	X =< Y, 
	ordered_([Y|Xs]).  
	

% permutation program --> very important 

permutation_([],[]). 
permutation_(Xs, [Y|Ys]):- 
	% choose one element to be the first 
	select(Y, Xs, Zs),
	%do the permutation of the others 
	permutation_(Zs, Ys). 
	
% implementing select 
select(X, [X|Xs], Xs). 
select(X, [Y|Xs], [Y|Zs]):- 
	Y \== X, 
	select(X, Xs, Zs). 

% 3.21 insertion sort

%supposing that Xs is already sorted 
insert(X, [Y|Xs], [X,Y|Xs]):-
		 X =< Y. 
insert(X, [Y|Xs], [Y|Ys]):- 
	X > Y, 
	insert(X, Xs, Ys). 
insert(X, [], [X]).

insertion_sort([], []). 
insertion_sort([X|Xs], Ys):-
	insertion_sort(Xs, Zs), 
	insert(X, Zs, Ys).