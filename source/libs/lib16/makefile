!include srcpath

libdir = $(lib_dir)\dos
aflags = -D_CRTBLD -I%ASMCDIR%\include\dos
lflags = -q -b -n -c

all: cs.lib cc.lib cl.lib

cs.lib:
    asmc $(aflags) -ms -r *.asm
    libw $(lflags) $(libdir)\$@ *.obj
    del *.obj
cc.lib:
    asmc $(aflags) -mc -r *.asm
    libw $(lflags) $(libdir)\$@ *.obj
    del *.obj
cl.lib:
    asmc $(aflags) -ml -r *.asm
    libw $(lflags) $(libdir)\$@ *.obj
    del *.obj

