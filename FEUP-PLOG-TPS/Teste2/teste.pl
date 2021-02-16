:- use_module(library(lists)).
:- use_module(library(clpfd)). 

% PERGUNTA 1
p1(L1,L2) :-
    gen(L1,L2),
    test(L2).

gen([],[]).
gen(L1,[X|L2]) :-
    select(X,L1,L3),
    gen(L3,L2).

test([]).
test([_]).
test([_,_]).
test([X1,X2,X3|Xs]) :-
    (X1 < X2, X2 < X3; X1 > X2, X2 > X3),
    test(Xs).
	

% PERGUNTA 3
p2(L1,L2) :-
    length(L1,N),
    length(L2,N),
    %
    pos(L1,L2,Is),
    all_distinct(Is),
    %
	test2(L2), 
    labeling([],Is).
    

pos([],_,[]).
pos([X|Xs],L2,[I|Is]) :-
    element(I,L2,X),
    pos(Xs,L2,Is). 
	
test2([]).
test2([_]).
test2([_,_]).
test2([X1,X2,X3|Xs]) :-
    (X1 #< X2 #/\ X2 #< X3) #\/ (X1 #> X2 #/\ X2 #> X3),
    test2(Xs).
	


% PERGUNTA 4 

sweet_recipes(MaxTime,NEggs,RecipeTimes,RecipeEggs,Cookings,Eggs):-
	length(Cookings, 3),
	length(RecipeTimes, RecipesSize), 
	domain(Cookings, 1,RecipesSize),
	all_distinct(Cookings),
	get_eggs(Cookings, RecipeEggs, Eggs), 
	get_time(Cookings, RecipeTimes, TotalTime), 
	
	Eggs #=< NEggs, 
	TotalTime #=< MaxTime, 
	
	append([Cookings, [Eggs]], Total),
	labeling([maximize(Eggs)], Total). 
	
get_eggs([], _,0).
get_eggs([Index|Cookings], RecipeEggs, TotalEggs):-
	element(Index, RecipeEggs, Eggs), 
	TotalEggs #= Eggs + OtherEggs, 
	get_eggs(Cookings, RecipeEggs, OtherEggs). 

get_time([], _, 0). 
get_time([Index|Cookings], RecipeTimes, TotalTime):-
	element(Index, RecipeTimes, Time), 
	TotalTime #= Time + OtherTime, 
	get_time(Cookings, RecipeTimes, OtherTime).
	




% PERGUNTA 5 

embrulha(Rolos, Presentes, RolosSelecionados):-
	length(Presentes, NumPresentes), 
	length(RolosSelecionados, NumPresentes), 
	length(Rolos, NumRolos), 
	domain(RolosSelecionados, 1, NumRolos), 
	
	generate_tasks(Tasks, RolosSelecionados, Presentes), 
	generate_machines(Machines, 1, Rolos), 
	
	cumulatives(Tasks, Machines, [bound(upper)]),
	
	labeling([], RolosSelecionados).
	
generate_tasks([], [], []). 
generate_tasks([task(1,1,2,Size,Index)|Tasks],[Index|RolosSelecionados], [Size|Presentes]):-
	generate_tasks(Tasks, RolosSelecionados, Presentes).


generate_machines([], _, []).
generate_machines([machine(Index, Size)|Machines],Index, [Size|Rolos]):-
	NewIndex is Index + 1, 
	generate_machines(Machines, NewIndex, Rolos).




























