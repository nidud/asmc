ifdef YACC

message:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

message.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 $*.asm
endif
	$@
endif
