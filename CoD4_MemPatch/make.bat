@echo off
windres resource.rc -O coff -o resource.res
gcc CoD4.c libColor/color.c resource.res -o CoD4_MemPatch.exe -s -m32