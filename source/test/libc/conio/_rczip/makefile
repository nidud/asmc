ifdef YACC
_rczip:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
_rczip.exe:
	asmc -q $*.asm
	linkw system con_32 name A32$@ file $*
	asmc -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	asmc64 -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	W64$@
	del *.obj
	del *.exe
	pause
endif
