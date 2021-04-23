#
# Makefile for Asmc using Visual C++ 6.0
#

!include srcpath

asmc.exe:
    cl -c -D_ASMC -DDEBUG -Gd -nologo -Zi -Od -Isrc\h src\*.c
    asmc -Zp4 -Cs -Isrc\h -Zi -coff -DDEBUG src\x86\*.asm
    link /debug /out:$@ /libpath:$(lib_dir) /subsystem:console *.obj crypt.lib
    @del *.obj
