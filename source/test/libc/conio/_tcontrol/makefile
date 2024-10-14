ifdef YACC
_tcontrol:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_tcontrol.exe:
	asmc64 -c -q -D__TTY__ $*.asm
	linkw sys tty_64 file $*
	$@
	del *.obj
	del *.exe
endif
