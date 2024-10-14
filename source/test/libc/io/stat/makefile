ifdef YACC
stat:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
stat.exe:
	asmc -c -q $*.asm
	linkw system con_32 name A32$@ file $*
	asmc -c -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	asmc64 -c -q $*.asm
	linkw system con_64 name A64$@ file $*
	asmc64 -c -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	asmc64 -c -q -pe $*.asm
	$@
	echo W64:
	W64$@
	del *.obj
	del *.exe
	pause
endif


