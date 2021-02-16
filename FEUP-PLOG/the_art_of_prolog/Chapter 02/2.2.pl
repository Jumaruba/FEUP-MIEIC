%database information 

course(complexity, time(monday, 9, 11), lecturer(david, harel), location(feinberg, a)).
course(calculus2,  time(monday, 10, 11), lecturer(david, harel), location(feinberg, a)).
course(introtobio, time(monday, 11, 12), lecturer(david, harel), location(feinberg, a)).
course(calculus1,  time(monday, 9, 11), lecturer(david, harel), location(feinberg, a)).

lecturer(Lecturer ,Course):-
		course(Course,Time,Lecturer,Location).

duration(Course ,Length) :-
		course(Course,time(Day,Start,Finish),Lecturer,Location),
		plus(Start, Length ,Finish).

teaches(Lecturer ,Day):-
	course(Course,time(Day,Start,Finish) ,Lecturer,Location).

occupied(Room,Day,Time):-
		course(Course,time(Day,Start,Finish),Lecturer,Room),
		Start =< Time,
		Time =< Finish.

% Requested 2.2 exercises 
%--------------------------------------------------------------------------------------------------------- 
% (i) define location(Course,Building),busy (Lecturer ,Time) and cannot_meet (Lecturerl ,Lecturer2).
% Test with your own course fact

location(Course, Building):- 
	course(Course, time(day, Start, Finish), Lecturer, location(Building, Room)).


% Case the term Time refers to the functor time 

busy(Lecturer, Time):- 
	course(Course, Time, Lecturer, Location). 

% My interpretation was cannot_meet must return 'yes' if two lecturers are not able to meet each other ever

%--------------------------------------------------------------------------------------------------------- 
%(ii) Define the relation scheddule_conflict (Time ,Place ,Coursel ,Course2).
% Remember the syntax: \= for variables and =\= for numbers 
schedule_conflict(Time, Place, Course1, Course2):-
	Course1 \= Course2,
	course(Course1, Time, Lecturer1, Place), 
	course(Course2, Time, Lecturer2, Place).
	
% test: schedule_conflict(Time, Place, calculus1, complexity).		
% In the way that this program is structured, we can have just 	two lectures with the exact same time. 	
		
%---------------------------------------------------------------------------------------------------------  
%(iii) 	1) Facts will be used to represent the courses that student has taken and grades 
% 	2) Rules will be used to enforce the college requirements
% For the degree the student must have grade higher than 7 in all of the courses.
% Just dont forget, elements with lower case. Variables with upper case! 

had_grade(took_course(josefino,calculus1), 8).

had_grade(took_course(josefino, complexity),9). 

had_grade(took_course(josefino, programming), 18). 
 

had_grade(took_course(carlos,calculus1), 8).

had_grade(took_course(carlos, complexity),9). 
 
had_grade(took_course(carlos, programming), 6). 

wasnt_approved(Student):-
		had_grade(took_course(Student, Course), Grade), 
		Grade < 7.	
		
% to test: 	wasnt_approved(carlos).   ==> expected: yes  	(he wanst approved) 
%		wasnt_approved(josefino). ==> expected: no 	(he was approved)
		
		
%---------------------------------------------------------------------------------------------------------  
%(iv) I didn't understand this point very well :P 	
		
		
		
		
		
		
		
		
		
		
		
