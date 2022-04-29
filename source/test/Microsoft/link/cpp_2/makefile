
main.exe:
    asmc64 -Cp -frame shape.asm
    cl /c /MD main.cpp
    link /subsystem:console main.obj shape.obj
    $@
    pause
    del *.obj
