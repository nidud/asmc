ifdef YACC

_tgetline:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

_tgetline.exe:
	asmc64 -c $*.asm
	linkw system con_64 file $*.obj
	$@
endif
