#!/bin/bash

binary="myteams_cli"
binaryTest="myteamsTest.txt"

echo -e "\e[34mAuto-Test functional $binary:\e[39m"

exit_status=0
declare -i nb=0
while read line
do
    nb=$nb+1
    returnCall=$(LD_LIBRARY_PATH=libs/myteams/ timeout --signal QUIT 60 ./$binary 127.0.0.1 2>&1)
    if ([[ $? == 0 ]])
    then
        echo -e "$nb : \e[31mTest KO : INVALIDE RETURN CODE | $returnCall\e[39m"
        exit_status=1
    else
        echo -e "$nb : \e[32mTest OUTPUT OK\e[39m"
        returnCall=$(./$binary $line 2>&1 > tests/tmp.txt)
        returnCall=$($binary $line 2>&1 > tests/res.txt)
    fi

done < tests/functional/$binaryTest
exit $exit_status