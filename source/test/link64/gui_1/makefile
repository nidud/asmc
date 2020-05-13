test.exe:
    asmc -win64 -ws -D_MSVCRT $*.asm
    link /map /libpath:%AsmcDir%\lib\amd64 /machine:x64 test.obj
    $@
    pause
    del $*.obj
    del $*.exe


