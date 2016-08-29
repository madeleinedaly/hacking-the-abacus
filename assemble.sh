#!/bin/bash

echo -e "BITS 64\n$1" >> tmp.asm && nasm tmp.asm -o tmp.bin
rm tmp.asm
if [ -f tmp.bin ]; then
    od -N 16 -t x1 tmp.bin && rm tmp.bin
fi
