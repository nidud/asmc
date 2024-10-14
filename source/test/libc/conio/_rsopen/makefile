ifdef YACC
_rsopen:
	asmc64 -c $@.asm
	asmc64 -c -idd res/OpenFile.idd
	gcc -nostdlib -o $@ $@.o OpenFile.o -l:libasmc.a
	./$@
	rm -f *.o
	rm -f $@
else
_rsopen.exe:
	asmc64 -c -q $*.asm
	asmc64 -c -idd res/OpenFile.idd
	linkw system con_64 file $*.obj, OpenFile.obj
	$@
	del *.obj
	del *.s
	del *.exe
endif
