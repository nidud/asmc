
main.exe:
    asmc64 -c -Cp -frame shape.asm
    cl /c /MD main.cpp
    link /subsystem:console /libpath:%AsmcDir%\lib\x64 main.obj shape.obj
    $@
    pause
    del *.obj
