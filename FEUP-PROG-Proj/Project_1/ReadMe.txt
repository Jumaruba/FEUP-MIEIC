----------------------------------------------------------------------------------
				~REPORT~
-----------------------------------------------------------------------------------

The program is working correctly as it is suppose to and all goals were achieved. 

However, there are a few considerations to be done that will be changed 
in the future for the next project: 

-The project is all commented, except for the file packs.cpp.
 
-Letters with accent will cause problems when formating the data to 
be visualized. 

-To change data about a client, the client's name is asked, instead 
of the NIF, because the client might not be portuguese and, consequently,
does not have a NIF. However a name can be repeated. So, for the next project 
the program will ask the NIF. 

-When creating a new package, the program asks the number of the new id, but  
it does not check if the if already exists. For the next project it will be checked 
or the atribution of a new ID will be automatic. 

--IMPROVEMENTS 

-The program checks if the day given by the user, for dates, is consistent with the month 
and year, analysing if it's a leap year how many days there're at this year. 

-The program does a safe file saving: first save the information in provisory files. 
When the process is done, the original files are deleted and the provisory files are 
renamed to the original files. 

-the program recognizes if the operational system is windows or linux and implement a function 
cleanScreen to clean the screen whichever the operational system is. 



