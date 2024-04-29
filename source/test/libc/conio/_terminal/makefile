ifdef YACC
_terminal:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_terminal.exe:
	asmc64 -q -D__TTY__ $*.asm
	linkw system tty_64 file $*
	$@
	del *.obj
	del *.exe
endif
