/* 
       (i) Write a program for substitute(X,Y,L1,L2), where L2 is the result of substituting Y for 
        all occurrences of X in L1.
        Note: remember that \== don't unify, but =\= unifies.  
*/

% Similiar to select and delete 

substitute(X,Y,[],[]). 
substitute(X,Y,[X|L1], [Y|L2]):- 
        substitute(X,Y,L1, L2). 
substitute(X,Y,[K|L1], [K|L2]):-
        K\==X,
        substitute(X,Y,L1,L2).


/*
        (ii)What is the meaning of the variant of select. 
        For me it's the same from the code_in_chapter_3.3.pl. We are deleting the first 
        occurrence of X in the list Xs. 
*/ 

select(X,[X|Xs], Xs). 
select(X, [Y|Ys], [Y|Zs]):- 
        X \== Y,
        select(X, Ys, Zs). 

/*
        (iii)Write a program for no_double(L1,L2), where L2 is the result of removing all duplicates 
        elements from L1. 
*/ 

no_doubles([X],[X]). 
no_doubles([X|Xs], Ys):- 
         member(X, Xs), 
         no_doubles(Xs,Ys). 
no_doubles([X|Xs], [X|Ys]):- 
        no_doubles(Xs, Ys). 