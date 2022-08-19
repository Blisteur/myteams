#!/bin/bash

sleep 2

declare -i nb=0
while read line
do
    nb=$nb+1
    echo -e "$nb : \e[34mTest $line user\e[39m"
    for (( c=1; c<=$line; c++ ))
    do
    	./tests/load/testFiles/client_dos.sh $1 $2 $3 &> /dev/null &
    done
    sleep 10
done < tests/load/$4
exit 0