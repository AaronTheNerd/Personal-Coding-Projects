#!/bin/bash
for size in 512 1024 2048 4096 8192 16384 32768 65536 131072
do
    for i in {1..50}
    do
        ./sort $size
    done
done
