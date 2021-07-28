
test.exe:
    asmc -win64 -D_MSVCRT $*.asm
    link /map /libpath:%AsmcDir%\lib\x64 /machine:x64 /subsystem:console test.obj
    $@
    pause
    #del $*.obj
    #del $*.exe


