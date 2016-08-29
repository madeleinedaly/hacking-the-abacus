#!/bin/bash

# gcc -std=gnu11 -g -Wall -o flip-bits flip-bits.c
# touch flip-bits.log
# > flip-bits.log

for i in {0..99}; do
    sudo ./flip-bits >> flip-bits.log;
done
