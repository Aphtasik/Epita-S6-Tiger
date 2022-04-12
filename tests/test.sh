#!/bin/sh

if [ "$#" -lt 1 ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Modify scipt as you want, given first arg in path to file"
else

    echo "##### TEST:"
    cat $1
    echo "##### OUTPUT.TIG:"
    ../src/./tc -XA $1 > output.tig
    cat output.tig
    echo "##### SECOND OUTPUT:"
    ../src/./tc -XA output.tig
fi

