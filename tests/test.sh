#!/bin/sh

if [ "$#" -lt 1 ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Modify scipt as you want, given first arg in path to file"
else
    ../src/./tc -X --parse-trace --parse $1 
fi

