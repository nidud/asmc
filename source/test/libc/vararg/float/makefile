ifdef YACC

float:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	@pause
	rm -f $@
	rm -f $@.o

else

float.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 $*.asm
	linkw system con_64 file $*.obj
endif
	$@
	pause
endif
