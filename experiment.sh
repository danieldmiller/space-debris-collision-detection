#!/bin/bash

for i in {1..4}
do
    for (( j=20; j<=500; j+=20 )) #Increment from 20-500 in steps of 20
    do
        TIME=$(./space-debris-collision-detection --thread-count $i --objects $j -cycles 1000 | grep "Program run time:")
        echo "Threads: $i, Objects: $j, Time: $TIME"
    done
done

