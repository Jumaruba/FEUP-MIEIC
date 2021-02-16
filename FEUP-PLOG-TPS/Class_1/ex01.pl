
parent(christina, michael).  
parent(aldo, lincoln).    
parent(aldo, michael). 

parent(michael, ella).
parent(sara, ella).

parnet(lisa, li).
parent(lincoln, li).

male(lincoln). 
male(aldo).   
male(li).
male(michael).

female(sara). 
female(lisa).
female(christina).   
female(ella).

father(X, Y):-
    parent(X, Y), 
    male(X). 

mother(X,Y):-
    parent(X,Y),
    female(X). 

son(X,Y):-
    parent(Y,X),
    male(X). 
    

daughter(X,Y):-
    parent(Y,X),
    female(X). 

% question a

parent(X, michael), famale(X). 

% question b 

parent(aldo, X), male(X). 
