#!/bin/bash

echo Compile...
./mtc $1 > $1".s"

if [ $? -ne 0 ]
then
	echo "Error(s) occured. Cannot continue compilation."
	exit;
fi

echo Generating object file...
as --march=i386 --32 $1".s" -o $1".o"

if [ $? -ne 0 ]
then
	echo "Error(s) occured. Cannot continue compilation."
	exit;
fi

echo "Linking..."
ld -m elf_i386 $1".o" -o $1".exe"

if [ $? -ne 0 ]
then
	echo "Error(s) occured. Cannot continue compilation."
	exit;
fi

echo "Program's output..."
./$1".exe"

echo "Program exit with value... $?"
echo "Compilation successful."

