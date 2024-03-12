#!/bin/bash

cd kernel

clang++ -I/usr/include -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -I/usr/include/x86_64-linux-gnu/c++/11 main.cpp \
-nostdlibinc -D__ELF__ -D_LDBL_EQ_DBL -D_GNU_SOURCE -D_POSIX_TIMERS \
-O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
-fno-exceptions -fno-rtti -std=c++17 -c main.cpp

ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static \
-o kernel.elf main.o hankaku.o

cd ..

rm img/kernel.elf
cp kernel/kernel.elf img/kernel.elf