@echo off
windres resource.rc -O coff -o resource.res
gcc ac4bf.c patchlib/patchlib.c resource.res -o ac4bf_trainer.exe -s -m32
pause
