@echo off
windres resource.rc -O coff -o resource.res
gcc ofdr.c libColor/color.c resource.res -o OFDR_MemPatch.exe -s -m32