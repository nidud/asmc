ifdef YACC

float:
	asmc64 -c -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	@pause
	rm -f $@
	rm -f $@.o

else

float.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 $*.asm
endif
	$@
	pause
endif
