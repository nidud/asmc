
main.exe:
    asmc64 -frame -nolib main.asm
    cl /c /GR- shape.cpp
    link /subsystem:console main.obj shape.obj
    $@
    pause
    del *.obj
