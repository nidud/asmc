_argv.exe:
	asmc -q $*.asm
	linkw N $@ Op q libp ..\..\..\lib L libo, kernel32 F ..\..\..\lib\c0.obj, $*.obj
	del $*.obj
	$@ 1 2 3 "4" 5 6 -7"quote" ""8" 9"
	pause


