test.exe:
	asmc64 -q -nolib $*.asm
	linkw op map lib msvcrt file $*
	$@
	pause
clean:
	del *.obj
	del *.exe
	del *.map

