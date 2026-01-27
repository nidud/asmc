
main.exe:
    asmc64 /c /Cp /frame /nolib shape.asm
    cl /c /MD main.cpp
    objconv -v0 -nr:?setWidth@Shape@@QEAAXH@Z:Shape_setWidth main.obj main2.obj
    objconv -v0 -nr:?setHeight@Shape@@QEAAXH@Z:Shape_setHeight main2.obj main.obj
    objconv -v0 -nr:?getArea@Rectangle@@QEAAHXZ:Rectangle_getArea main.obj main2.obj
    objconv -v0 -nr:?Rect@@3PEAVRectangle@@EA:Rect main2.obj main.obj
    link /libpath:%AsmcDir%\lib\x64 main.obj shape.obj msvcrt.lib
    $@
    pause
    del *.obj
