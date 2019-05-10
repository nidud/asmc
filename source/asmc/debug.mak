#
# Makefile for Asmc using Visual C++ 6.0
#

LIB = %AsmcDir%\lib

asmc.exe:
    cl -c -D_ASMC -DDEBUG -Gd -nologo -Zi -Od -Isrc\h src\*.c
    asmc -Isrc\h -Zi -coff -DDEBUG src\x86\*.asm
    link /debug /out:$@ /libpath:$(LIB) /subsystem:console *.obj
    @del *.obj
