@echo off
windres resource.rc -O coff -o resource.res
gcc bf3.c patchlib/patchlib.c resource.res -o bf3_trainer.exe -s -m32
pause
