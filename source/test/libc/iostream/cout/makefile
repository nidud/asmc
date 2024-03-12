ifdef YACC
cout:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
cout.exe:
	asmc64 $*.asm
	asmc64 stdio.asm
	linkw system con_64 file $*
	linkw system con_64 file stdio
	del *.obj
	echo cout.exe:
	$@
	echo stdio.exe:
	stdio
	pause
	del *.obj
	del *.exe
endif
