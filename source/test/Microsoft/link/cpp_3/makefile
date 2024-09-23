
main.exe:
    asmc64 -frame -nolib main.asm
    cl /c /GR- shape.cpp
    link /subsystem:console /libpath:%AsmcDir%\lib\x64 main.obj shape.obj
    $@
    pause
    del *.obj
