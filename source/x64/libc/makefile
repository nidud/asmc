LIBDIR = %AsmcDir%\lib\x64
INCDIR = %AsmcDir%\include

all: $(LIBDIR)\libc.lib $(LIBDIR)\libd.lib

$(LIBDIR)\libc.lib:
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -r *.asm
	libw -q -t -s -b -n -c -fac $@ *.obj
	del *.obj

$(LIBDIR)\libd.lib:
	asmc -nologo -I$(INCDIR) -Zi -win64 -D_WIN64 -DDEBUG -r *.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

