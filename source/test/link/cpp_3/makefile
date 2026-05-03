
main.exe:
    asmc64 -c -frame -nolib main.asm
    cl /c /GR- shape.cpp
    link /subsystem:console /libpath:%AsmcDir%\lib\x64 main.obj shape.obj
    $@
    pause
    del *.obj
