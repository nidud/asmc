LIBDIR = \Asmc\lib
INCDIR = \Asmc\include

$(LIBDIR)\libd.lib:
	asmc -nologo -Cs -I$(INCDIR) -Zi -DDEBUG -coff -r *.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
