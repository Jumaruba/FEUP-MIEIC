#!/bin/bash

simpledu_location="${HOME}/Documents/SOPE/SOPE-proj1/simpledu"

command_args="-l -a -L"
dir="/home/tiago/.cache"

echo "Dir: $dir"
echo ${simpledu_location} ${command_args} ${dir}
(${simpledu_location} ${command_args} ${dir} 2>"/dev/null" || echo $?) | sort -k2 > /tmp/testeT_simpledu.txt
(du ${command_args} ${dir} 2>"/dev/null" || echo $?) | sort -k2 > /tmp/testeT_du.txt
diff --suppress-common-lines /tmp/testeT_simpledu.txt /tmp/testeT_du.txt
diff -q /tmp/testeT_simpledu.txt /tmp/testeT_du.txt > /dev/null 2>&1 && echo OK || echo FAILED

