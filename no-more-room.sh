#!/bin/bash


available() {
    local chunks
    read -r -a chunks <<< $(df | awk '{print $4}')
    unset "chunks[0]" # drop column header

    local bytes=0
    for chunk in "${chunks[@]}"; do
        let bytes+=$chunk
    done

    echo "$bytes"
}


dest=/tmp/filler.lol
bytes=$(available)
gigabytes=$(bc <<< "scale=2; $bytes / 1024^2")
# truncated=${gigabytes%.*}

echo "./$(basename $0): writing $gigabytes GB to $dest"
dd if=/dev/urandom iflag=fullblock | pv | dd of=$dest bs=4096
