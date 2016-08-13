#!/bin/bash

read -r -a pids <<< $(ps -e | awk '{print $1}' | sort -rn)
unset "pids[-1]" # drop "PID" column header

for pid in "${pids[@]}"; do
    if [[ $pid -eq $$ ]]; then
        echo 'skipping $$:' $pid
        continue
    else
        echo "killing $pid"
        kill -s SIGINT $pid
    fi
done

echo 'killing $$:' $$
kill -s SIGINT $$
