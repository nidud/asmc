ifdef YACC
float2:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
float2.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del *.exe
endif

