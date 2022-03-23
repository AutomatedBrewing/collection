#!/bin/sh

export CC=gcc
export CXX=g++
export AR=ar
export LD=ld
export SIZE=size
export CFLAGS='-std=c99 -O3 -Wall -Wextra -Wpedantic -fstack-usage -Wstack-usage=512 -ffunction-sections -fdata-sections -fno-strict-aliasing'

make clean
echo "Flash and static RAM required for system $(uname -a):"
echo "gcc version: $(gcc --version)"
make -j coll > size_linux.txt 2> warnings.txt
echo "Max stack usage found for function: $(cat $(make coll_su) | sort -k2 -n | tail -n1 | awk -F ":" '{print $4}' | awk '{print $1 " " $2}')" >> size_linux.txt
cat size_linux.txt
