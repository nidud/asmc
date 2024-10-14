ifdef YACC

ctype:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	@rm $@.o
	@rm $@

else

ctype.exe:
	echo MSVCRT:
	asmc64 -c -q -pe $*.asm
	$@
	echo LIBC:
	asmc64 -c -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
	del $*.obj
	del $*.exe
endif
