@echo off
if [%1] == [] (
    echo Usage: asmtobin name
    exit
)
asmc64 -q -bin -Fo bin\%1.bin asm\%1.asm
REM ml64 -nologo -c asm\%1.asm > NUL
REM cbin %1.obj bin\%1.bin
REM del %1.obj