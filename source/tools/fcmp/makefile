ifdef YACC

fcmp:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

fcmp.exe:
	asmc64 -pe $*.asm

endif
