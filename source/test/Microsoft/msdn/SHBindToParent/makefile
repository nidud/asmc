SHBindToParent.exe:
	asmc -q -pe -Fo $*_pe32.exe $*.asm
	asmc -q -pe -win64 -Zp8 -Fo $*_pe64.exe $*.asm
	asmc -c -q -Fo $*_32.obj $*.asm
	linkw system con_32 file $*_32
	asmc -c -q -win64 -Zp8 -Fo $*_64.obj $*.asm
	linkw system con_64 file $*_64
	del *.obj
	dir *.exe | find ".exe"
	pause

