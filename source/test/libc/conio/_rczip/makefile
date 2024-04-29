ifdef YACC
_rczip:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rczip.exe:
	asmc64 -q $*.asm
	linkw system tty_64 file $*
	$@
	del *.obj
	del *.exe
endif
