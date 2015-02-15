#!/bin/bash

for file in tests/*.mtc ; do
    echo [ Running $file ]
    ./mtc.sh $file
    echo
done

