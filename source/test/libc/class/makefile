ifdef YACC
class:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
class.exe:
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
