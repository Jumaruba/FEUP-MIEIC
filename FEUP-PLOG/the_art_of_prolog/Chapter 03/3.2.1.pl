% (i) -----------------------------------------------------------------------------------------
% when it's typed subsequence(Xs, [Y| Ys]) :- subsequence(Xs, Ys) we are agreeing that
% even if the first term of Xs isn't Y, we are proceeding with the recursion, when actually 
% it should return false. 

subsequence_([X|Xs], [X|Ys]):-
        subsequence_(Xs,Ys).                    %that's ok for now 
subsequence_(Xs, [Y|Ys]):-
        subsequence_(Xs,Ys). 
subsequence_([], Ys). 

% this sequence actually doesn't need to be continuos. 
% For example, for Xs = [a,d] and Ys = [a,b,c,d], we have that Xs is a subsequence
% of the list Ys. Sublist would return false. 


%(ii) -----------------------------------------------------------------------------------------

adjacent_(X,Y,[X,Y|Zs]). 
adjacent_(X,Y,[C|Zs]):-
        adjacent_(X,Y,Zs). 

%to test: adjacent_(a,b,[a,c,d,b]). => no
%to test: adjacent_(a,b,[d,e,f,a,b,g]). => yes

last_(X,[X]).
last_(X, [A|Zs]):-
        last_(X, Zs). 

%to test: last_(a,[v,c,d,e,a]). => yes 
%to test: last_(a, [a,b,c,d,e]). => no

%(iii) ----------------------------------------------------------------------------------------

%The first hypoteses is that the elements repeats in sequence
double([X], [X,X]).  
double([X|Xs], [X,X|Ys]):- 
        double(Xs, Ys). 

%to test: double([1,2,3],Ys). => Ys = [1,1,2,2,3,3] ? 

%I don't know how to do it if there isn't an especific order..... 

%(v) ------------------------------------------------------------------------------------------

%(a) Using plus/3 

plus(X,Y,Z):-
        Z is X + Y.

sum([], 0). 
sum([X|Xs], Y):-
        sum(Xs, Z),
        plus(X,Z,Y).
        
%(b) Whitout using auxiliar predicates 

sum_([],0). 
sum_([X], X). 
sum_([X|Xs], Z):-
        sum(Xs, K),
        Z is K + X. 

% I dont know if using Z is K + X is actually allowed here... 