test.exe:
    asmc64 -ws -frame $*.asm
    link /libpath:%AsmcDir%\lib\x64 /machine:x64 $*.obj
    $@
    pause
    del $*.obj


