LIBDIR = ..\..\lib
INCDIR = ..\..\include

$(LIBDIR)\libo.lib:
	iddc -r *.idd
	asmc -nologo -Cs -I$(INCDIR) -r *.asm
	libw -q -t -s -b -n -c $@ *.obj
	del *.obj

$(LIBDIR)\libc.lib:
	asmc -nologo -Cs -I$(INCDIR) -D__WXP__ -coff -r *.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

$(LIBDIR)\libd.lib:
	asmc -nologo -Cs -I$(INCDIR) -Zi -DDEBUG -coff -r *.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
