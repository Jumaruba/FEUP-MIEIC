:-use_module(library(clpfd)). 
:-use_module(library(lists)). 



optimal_skating_pairs(MenHeights, WomenHeights, Delta, Pairs):- 
	
	length(MenHeights, Size), 

	
	% Declare and domain
	length(SelectedWomen, Size), 
	domain(SelectedWomen, 1, Size), 
	findall(N, between(1, Size, N), SelectedMen), 
	
	% Constraints 
	all_distinct(SelectedWomen), 
	all_distinct(SelectedMen),
	
	choose_women(MenHeights, WomenHeights, SelectedMen, SelectedWomen, Delta), 
	
	generate_pairs(SelectedMen, SelectedWomen, Pairs_), 
	length(Pairs_, PairsSize), 
	
	labeling([maximize(PairsSize)], SelectedWomen), 
	
	
	
	
choose_women(_,_,[],[], _).
choose_women(MenHeights, WomenHeights,  [MenPos|SelectedMen], [WomanPos|SelectedWomen], Delta):-
	nth1(MenPos, MenHeights, Men), 
	element(WomanPos, WomenHeights, Woman), 
	abs(Men-Women) #< Delta, 
	Men #> Women, 
	choose_women(MenHeights, WomenHeights, SelectedMen, SelectedWomen, Delta), !.
	
choose_women(MenHeights, WomenHeights, [MenPos|SelectedMen], [0|SelectedWomen], Delta):- 
	choose_women(MenHeights, WomenHeights, SelectedMen, SelectedWomen, Delta). 
	
generate_pairs([], [], []).
generate_pairs([MenPos|SelectedMen], [WomanPos|SelectedWomen], [MenPos-WomenPos|Pairs]):-
	WomanPos #\= 0, !,
	generate_pairs(SelectedMen, SelectedWomen, Pairs).
generate_pairs([MenPos|SelectedMen], [_|SelectedWomen], Pairs):-
	generate_pairs(SelectedMen, SelectedWomen, Pairs). 
	
