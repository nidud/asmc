ifdef YACC
_cout:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
_cout.exe:
	asmc -q $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@
	asmc -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	W32$@
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@
	asmc64 -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	W64$@
	pause
	del *.obj
	del *.exe
endif
