pi:
ifdef YACC
	asmc -c -q -elf pi.asm
else
	asmc -c -q pi.asm
endif
	asmc64 -c -q pi.asm
	pause
ifdef YACC
	rm  $@.o
else
	del $@.obj
endif
