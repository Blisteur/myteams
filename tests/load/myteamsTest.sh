#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "USAGE: $0 host port"
    exit 0
fi

binary="myteams_cli"
binary2="./myteams_server"
binaryTest="myteamsTest.txt"

echo -e "\e[34mAuto-Test load $binary:\e[39m"
./tests/load/testFiles/client_script.sh $binary $1 $2 $binaryTest 2> /dev/null &
returnCall=$(LD_LIBRARY_PATH=libs/myteams/ timeout --signal QUIT 60 ./$binary2 $2)
if ([[ $? == 0 ]])
then
    echo -e "\e[31mTest KO : Charge to hight | $returnCall\e[39m"
    exit 1
else
    echo -e "\e[32mTest OK\e[39m"
fi
exit 0