ifdef YACC
_atodbl:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
_atodbl.exe:
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@
	asmc -q -8 $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
