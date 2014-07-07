@echo off
windres_x64 resource.rc -O coff -o resource.res
gcc_x64 bf4.c patchlib/patchlib.c resource.res -o bf4_trainer.exe -s -m64
pause
