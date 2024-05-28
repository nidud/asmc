ifdef YACC

exec:
	asmc64 -q $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	asmc64 -fpic args.asm
	gcc -o args args.o
	./$@ ./args 2
	rm *.o
else

exec.exe:
	asmc64 -q $*.asm
	linkw system con_64 file $*.obj
	asmc64 -q -pe args.asm
	$@ args.exe 2
	pause
	del $*.obj
endif
