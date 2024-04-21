ifdef YACC

_tgetline:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

_tgetline.exe:
	asmc64 $*.asm
	linkw system con_64 file $*.obj
	$@
endif
