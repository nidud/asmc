ifdef YACC

spawn:
	asmc64 -c -q $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	asmc64 -q -fpic ../exec/args.asm
	gcc -o args args.o
	./$@ 2 ./args
	@pause
	rm -f *.o
	rm -f ./$@
	rm -f ./args

else

spawn.exe:
	asmc64 -c -q $*.asm
	linkw system con_64 file $*.obj
	asmc64 -c -q -pe ../exec/args.asm
	$@ 2 args.exe
	pause
	del $*.obj
endif
