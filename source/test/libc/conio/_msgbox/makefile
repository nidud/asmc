ifdef YACC
_msgbox:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_msgbox.exe:
	asmc64 -c $*.asm
	linkw sys tty_64 file $*
	$@
	del *.exe
	del *.obj
endif
