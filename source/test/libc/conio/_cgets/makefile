_cgets:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	rm -f $@.o
	rm -f $@
else
	$@
	asmc -q -coff $@.asm
	$@
	asmc -q -coff -ws $@.asm
	$@
	asmc64 -q -ws $*.asm
	$@
	del $@.obj
	del $@.exe
	pause
endif

