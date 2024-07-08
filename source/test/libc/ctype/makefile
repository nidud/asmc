ifdef YACC

ctype:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

ctype.exe:
	echo MSVCRT:
	asmc64 -q -pe $*.asm
	$@
	echo LIBC:
	asmc64 -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
	del $*.obj
	del $*.exe
endif
