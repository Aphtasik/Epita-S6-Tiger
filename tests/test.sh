#!/bin/sh

if [ "$#" -lt 1 ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Modify scipt as you want, given first arg in path to file"
else
    echo "##### TESTS"
    cat $1
    echo "##### OUTPUT"
    ../src/./tc -XA $1 > output
    cat output
    echo "##### SECOND OUTPUT"
    ../src/./tc -XA output
fi

