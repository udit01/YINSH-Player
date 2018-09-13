#!/bin/bash

## To run main.cpp
if [ -e "player" ]; then
    ./player
else
    echo "First run compile.sh to compile the code"
fi