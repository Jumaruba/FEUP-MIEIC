% This are some functions that were done before seeing the code in the book. 
% They are standard of the language, but it's important to understand how it works. 

% recursive solution for natural numbers. Using induction: s(X) is the next number. So x+1 is natural if x is natural too. 

natural_number(0). 
natural_number(s(X)):-
        natural_number(X). 

% we are considering that s^n(0) represents the number n. So, to test this program, we need to give an input like s(s(0)). 

%CHECK A MEMBER OF A LIST ----------------------------------------------------

% A list is consisted of [head|list]. 
member_(X, [X|Xs]).
member_(X, [Y|Ys]):-
        member(X, Ys). 


% test: mem(b, [a|[b|[c|[]]]]). 

%SUFIX AND PREFIX FUNCTIONS --------------------------------------------------- 

%PREFIX: Have in consideration the following list [a,b,c,d,e]. We have that the 
% list [a,b] is the prefix of this function, so as [a,b,c], [a,b,c,d] and so on. 
% To indentify this our, function would be: 
    
prefix_([], Ys). 
prefix_([X|Xs], [X|Ys]):-
        prefix_(Xs, Ys). 

%SUFIX: Have the previous array in consideration [a,b,c,d,e]. Now, the list [d,e] is 
%the sufix of the list, so as [c,d,e] and so on.

sufix_(Xs, Xs). 
sufix_(Xs, [Y, Ys]):-
        sufix_(Xs, Ys). 

%SUBLIST OF A LIST: Actually there are several ways to do this. One way is to find 
%the prefix of a sufix or the opposite. Those are not the only way to this., 
 
sublist_(Xs, Ys):- 
        sufix_(Ks, Ys), 
        prefix_(Xs, Ks). 
                    
%APPEND TWO LISTS  ------------------------------------------------------------ 

%append all the elements of a list. This is not intuitive at all . 
append_([], Ys, Ys).
append_([X|Xs], Ys, [X|Zs]):- 
        append(Xs, Ys, Zs). 


% REVERSE A LIST ---------------------------------------------------------------

%we can do it by appending the values to an empty list. This one I couldn't do it by 
%my on, so looked the answer... :( 

%Xs - list to be reverted; Ys - reverted list 
reverse_([],[]). 
reverse_([X|Xs], Zs):- 
        reverse_(Xs, Ys),
        append(Ys, [X], Zs). 

% This second way is more intuitive

reverse_2(Xs, Ys):- 
        reverse_2(Xs, [], Ys).   %overload the function 

reverse_2([X|Xs], Acc, Ys):- 
        reverse_2(Xs, [X|Acc], Ys). 

reverse_2([], Ys, Ys).          % attributes                        

% LENGTH ------------------------------------------------------------------------

% To get the length of the list, remember the use of the functor s(X). 

length_([], 0). 
length_([X|Xs], s(N)):-
        length(Xs, N). 
