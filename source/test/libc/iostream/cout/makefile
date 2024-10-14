ifdef YACC
cout:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
cout.exe:
	asmc64 -c $*.asm
	asmc64 -c stdio.asm
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
