#!/bin/bash

regexError='error:'
regexWarning='warning:'

if test -f $1 && ! test -h $1
then
    echo "File exists" >> log.txt
else
    echo "File does not exist"
    exit 1;
fi
out="log.txt"
gcc -Wall $1 2> $out
errorCount=0
warningCount=0
for entry in `cat $out`
do
    if [[ $entry =~ $regexError ]]
    then
        errorCount=`expr $errorCount + 1`
    fi
done


for entry in `cat $out`
do
    if [[ $entry =~ $regexWarning ]]
    then
        warningCount=`expr $warningCount + 1`
    fi
done
echo "Nr of errors in $1: $errorCount"
echo "Nr of warnings in $1: $warningCount"
