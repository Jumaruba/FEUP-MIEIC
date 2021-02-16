% stack on block can be defined by a collection of facts on(Block1, Block2) 
% let's imagine a vector as a stack where the end is the top v = {a,b,c,d,e,f,g} 
 
on(b,a).
on(c,b). 
on(d,c).
on(e,d).
on(f,e).
on(g,f). 


above(Block, Block). 
above(Block1, Block2):-
        on(Block1, Link), 
        above(Link, Block2).  

%to test: above(f,b) => yes
%         above(d,e) => no

%----------------------------------------------------------------------------------------------------------------------
%Add recursive rules for left_of and above
%define higher(Objectl,Object2),which is true if Objecti is on a line higher than Object2


left_of(pencil, timer). 
left_of(timer, butterfly). 
left_of(butterfly, fish). 
left_of(cam, fish). 
left_of(byke, timer). 


on(cam, butterfly). 
on(byke, pencil). 

% The point here is that we must define that if a object is the left of itself, then all the 
% object above or below the same object must have left_rec true.
% That isn't intuitive, since it's strange to say that an object is on the left of itself and the objects above and below. 
left_rec(Obj, Obj). 
left_rec(Obj1, Obj2):-
        above(Obj1, Obj2).
left_rec(Obj1, Obj2):- 
        above(Obj2, Obj1). 
left_rec(Obj1, Obj2):-
        left_of(Obj1, Linker), 
        left_rec(Linker, Obj2).



% above(byke, timer) -> left_of(timer, butterfly) -> left_rec(butterfly, cam). 
% above(butterfly, butterfly), 
%to test: left_of(pencil, fish).  => yes
%         left_of(byke, fish). => yes 
%         left_of(cam, byke). => no

%----------------------------------------------------------------------------------------------------------------------



edge(a,b). 
edge(a,c).
edge(b,d).
edge(c,d).
edge(d,e). 
edge(f,g).

% Something new learned. We can attribute a value to a variable as Y is X+1. 
plus(X,1,Y):-
        Y is X+1.  

connected(Node,Node, 0).
connected(Node1,Node2, X):-
        edge(Node1, Link), 
        connected(Link, Node2,Y), 
        plus(Y,1,X). 

        














