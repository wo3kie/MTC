#!/bin/bash

if [ "$1" = "clean" ]
then
    rm ./tests/*.s
    rm ./tests/*.o
    rm ./tests/*.exe

    exit;
fi

for current_test in ./tests/*.mtc
do
    ./mtc $current_test > $current_test".s"
    as $current_test".s" -o $current_test".o"
    ld $current_test".o" -o $current_test".exe"
    ./$current_test".exe"

    result=$?

    if [ $result -eq 0 ]
    then
        echo "OK   -  '$current_test'"
    elif [ $result -ne 0 ]
    then
        echo "FAIL -  '$current_test' -  $result"
    fi
done

