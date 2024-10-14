ifdef YACC

_aligned_offset_malloc:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

_aligned_offset_malloc.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 -c -assert $*.asm
	linkw system con_64 file $*.obj
endif
	$@
	pause
endif
