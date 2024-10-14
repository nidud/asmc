ifdef YACC
_cgets:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_cgets.exe:
	asmc -c -q $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@
	asmc -c -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	W32$@
	asmc64 -c -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@
	asmc64 -c -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	W64$@
	del *.obj
	del *.exe
	pause
endif

