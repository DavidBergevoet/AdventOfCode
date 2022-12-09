#!/bin/bash

EXAMPLE_DAY_PATH="ExampleDay/"

if [ $# -ne 2 ]; then
    echo "Script must be called with: <year> <day>"
    exit 1
fi

DAY=${2}

if [ ${#2} -eq 1 ]; then
    DAY="0$2"
fi

if [ ${#DAY} -ne 2 ]; then
    echo "Day must be 1 or 2 characters"
    exit 2
fi

DAY_PATH="$1/Day-$DAY/"

mkdir $DAY_PATH > /dev/null

if [ $? -ne 0 ]; then
    echo "Could not make path: '$DAY_PATH'"
    exit 3
fi

cp $EXAMPLE_DAY_PATH* $DAY_PATH

if [ $? -ne 0 ]; then
    echo "Could not copy from '$EXAMPLE_DAY_PATH' to '$DAY_PATH'"
    exit 4
fi