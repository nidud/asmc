ifdef YACC
findfirst:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@ "*.*"
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
findfirst.exe:
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@ *.*
	asmc64 -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	W64$@ *.*
	asmc64 -q -pe $*.asm
	$@ *.*
	pause
	del *.obj
	del *.exe
endif
