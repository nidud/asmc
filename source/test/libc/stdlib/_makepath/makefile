ifdef YACC
_makepath:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_makepath.exe:
	asmc -q $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
