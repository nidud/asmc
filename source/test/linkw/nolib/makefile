test.exe:
	asmc64 -q -nolib $*.asm
	linkw op map lib %ASMCDIR%/lib/x64/msvcrt file $*
	$@
	pause
clean:
	del *.obj
	del *.exe
	del *.map

