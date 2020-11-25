#!/bin/bash

objdump=~/.arduino15/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-objdump
objs="build/{clock,drums,hal,misc,osc,pattern}.cpp.o"
eval $objdump $objs -d | c++filt | grep -vE '^\s+\.'
