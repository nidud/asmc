
main.exe:
    asmc64 -frame -nolib main.asm
    cl /c shape.cpp
    link /subsystem:console main.obj shape.obj
    $@
    pause
    del *.obj
