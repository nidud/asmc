ifdef YACC

ti:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

ti.exe:
	asmc -q $*.asm
	linkw op q symt _cstart file $*
	$@
	del *.obj
	pause
endif
