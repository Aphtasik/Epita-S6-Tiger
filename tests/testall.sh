#!/bin/sh

touch errors
rm errors
for f in alltests/*; do
    ../src/./tc -AX $f > output
    var=$?
    if [ "$var" -ne 0 ]; then
        echo "Failed on FIRST PARSE of $f with exit code $var" >> errors 
    fi
    ../src/./tc -AX output
    var=$?
    if [ "$var" -ne 0 ]; then
        echo "Test failed on SECOND PARSE $f with exit code $var" >> errors
    fi
done
echo "##### ERRORS:"
cat errors

