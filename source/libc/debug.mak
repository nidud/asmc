LIBDIR = %AsmcDir%\lib
INCDIR = %AsmcDir%\include

$(LIBDIR)\libd.lib:
	iddc -r *.idd
	asmc -nologo -Cs -I$(INCDIR) -Zi -DDEBUG -coff -r *.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
