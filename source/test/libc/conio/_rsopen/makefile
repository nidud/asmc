ifdef YACC
_rsopen:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
_rsopen.exe:
	asmc64 -q $*.asm
	linkw system con_64 file $*
	$@
	pause
	del *.obj
	del *.exe
endif
