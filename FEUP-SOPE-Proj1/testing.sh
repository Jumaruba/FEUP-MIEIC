#!/bin/bash

simpledu_location="${HOME}/Documents/SOPE/SOPE-proj1/simpledu"

directories_file="${HOME}/Documents/SOPE/SOPE-proj1/directories_to_test.txt"

command_args=(
    "-l -a"                          # 0
    "-l -a -L"                       # 1
    "-l -a -L --max-depth=0"         # 2
    "-l -a -L -S --max-depth=0"      # 3
    "-l -a -L --max-depth=1"         # 4
    "-l -a -L -S --max-depth=1"      # 5
    "-l -a -L --max-depth=2"         # 6
    "-l -a -L -S --max-depth=1"      # 7
    "-l -a -L -B 25"                 # 8
    "-l -a -L -S -B 25"              # 9
    "-l -a -B 25"                    # 10
    "-l -a -b"                       # 11
    "-l"                          # 12
    "-l -L"                       # 13
    "-l -L --max-depth=0"         # 14
    "-l -L -S --max-depth=0"      # 15
    "-l -L --max-depth=1"         # 16
    "-l -L -S --max-depth=1"      # 17
    "-l -L --max-depth=2"         # 18
    "-l -L -S --max-depth=1"      # 19
    "-l -L -B 25"                 # 20
    "-l -L -S -B 25"              # 21
    "-l -B 25"                    # 22
    "-l -b"                       # 23
)

while read dir;
do
    echo "Dir: ${dir}"
    for i in ${!command_args[*]}
    do
        echo -n "Test no. $i: "
        (${simpledu_location} ${command_args[$i]} ${dir} 2> /dev/null || echo $?) | sort -k2 > /tmp/testeT_simpledu.txt
        (du ${command_args[$i]} ${dir} 2> /dev/null || echo $?) | sort -k2 > /tmp/testeT_du.txt
        diff -q /tmp/testeT_simpledu.txt /tmp/testeT_du.txt > /dev/null 2>&1 && echo OK || echo FAILED
        
        # Uncomment line below to print what's wrong (in case of test failed)
        # diff -y /tmp/testeT_simpledu.txt /tmp/testeT_du.txt
    done
done < $directories_file
