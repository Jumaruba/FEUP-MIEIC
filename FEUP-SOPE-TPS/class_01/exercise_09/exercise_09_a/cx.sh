!/bin/bash

if [rm *.o]; then
	echo ".o FILES REMOVED SUCCESSFULLY";
else
	echo "NO .o FILES TO BE REMOVED"; 
fi

echo "Name of the file: $1"; 
mv $1 $1.c
if gcc $1.c -Wall; then
	echo "COMPILED";
else
	echo "COMPILATION ERROR";

fi
mv $1.c $1


