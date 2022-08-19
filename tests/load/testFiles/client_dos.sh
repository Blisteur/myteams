#!/bin/bash

LD_LIBRARY_PATH=libs/myteams/ ./$1 $2 $3 <<EOF
/login "test"
EOF