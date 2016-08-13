#!/bin/bash

read -r -a chunks <<< $(df | awk '{print $4}')
unset "chunks[0]" # drop "Available" column header

size=0
for chunk in "${chunks[@]}"; do
    let size+=$chunk
done

dest=/tmp/filler.lol
echo "$(basename $0): writing $size random bytes to $dest"
dd if=/dev/urandom iflag=fullblock | pv | dd of=$dest bs=1024 count=$size
