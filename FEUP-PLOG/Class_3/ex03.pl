% Concatenate two lists 

append_([], L2, L2). 
append_([X|L1], L2, [X|L]):- 
	append_(L1, L2, L). 

