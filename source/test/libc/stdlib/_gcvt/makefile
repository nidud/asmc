ifdef YACC
_gcvt:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_gcvt.exe:
	asmc64 -c -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@
	asmc -c -q -8 $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@
	asmc64 -c -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif