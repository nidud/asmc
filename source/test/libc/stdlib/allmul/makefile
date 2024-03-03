ifdef YACC
allmul:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
allmul.exe:
	asmc -q $*.asm
	linkw system con_32 name A32$@ file $*
	asmc -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	asmc64 -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	echo A32:
	A32$@
	echo W64:
	W64$@
	del *.obj
	del *.exe
	pause
endif
