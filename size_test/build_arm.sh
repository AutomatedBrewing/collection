#!/bin/sh

if [ -z ${ARM_GCC_PATH+x} ]; then
    ARM_GCC_PATH=/usr/bin
fi

export CC=$ARM_GCC_PATH/arm-none-eabi-gcc
export CXX=$ARM_GCC_PATH/arm-none-eabi-g++
export AR=$ARM_GCC_PATH/arm-none-eabi-ar
export LD=$ARM_GCC_PATH/arm-none-eabi-ld
export SIZE=$ARM_GCC_PATH/arm-none-eabi-size
export CFLAGS='-std=c99 -Os -Wall -Wextra -Wpedantic -fstack-usage -Wstack-usage=128 -ffunction-sections -fdata-sections -fno-strict-aliasing -mcpu=cortex-m0 -mthumb -mabi=aapcs -mfloat-abi=soft'

make clean
echo "arm-none-eabi-gcc version: $($CC --version)"
echo "CFLAGS: $CFLAGS"
make -j coll > size_arm.txt 2> warnings.txt
echo "Max stack usage found for function: $(cat $(make coll_su) | sort -k2 -n | tail -n1 | awk -F ":" '{print $4}' | awk '{print $1 " " $2}')" >> size_arm.txt
cat size_arm.txt