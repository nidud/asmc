ifdef YACC
float3:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
float3.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del $@
endif
