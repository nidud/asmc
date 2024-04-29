ifdef YACC

_readinput:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@

else

_readinput.exe:
	asmc64 -D__TTY__ $*.asm
	linkw sys tty_64 file $*.obj
	$@
	del $*.obj
	del $*.exe
endif
