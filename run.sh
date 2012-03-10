#!/bin/bash
echo "
target remote localhost:3333
monitor reset halt
load out/TestI2C.elf
monitor reset run
quit
" > tmp

arm-none-eabi-gdb out/TestI2C.elf -x tmp -q

rm tmp

