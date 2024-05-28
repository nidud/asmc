ifdef YACC

exec:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	asmc64 -fpic args.asm
	gcc -nostdlib -o args args.o -l:libasmc.a

else

exec.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 $*.asm
	linkw system con_64 file $*.obj
	asmc64 args.asm
	linkw system con_64 file args.obj
endif
	$@
	pause
endif
