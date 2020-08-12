test.exe:
    asmc -win64 -ws -D_MSVCRT $*.asm
    link /map /libpath:%AsmcDir%\lib\x64 /machine:x64 test.obj
    $@
    pause
    del $*.obj
    del $*.exe


