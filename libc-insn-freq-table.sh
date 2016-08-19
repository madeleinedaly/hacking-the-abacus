#!/bin/sh

objdump -d --no-show-raw-insn /lib64/ld-linux-x86-64.so.2 | awk '{print $2}' | sort | uniq -c | sort -nr
