ifdef YACC
_rczip:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rczip.exe:
	asmc64 -c -q $*.asm
	linkw system tty_64 file $*
	$@
	del *.obj
	del *.exe
endif
