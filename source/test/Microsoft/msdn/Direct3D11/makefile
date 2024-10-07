Tutorial.exe:
	asmc   -q -peg -Fo$*0132.exe -ws $*01.asm
	asmc64 -q -peg -Fo$*0164.exe -ws $*01.asm
	asmc   -q -peg -Fo$*0232.exe $*02.asm
	asmc64 -q -peg -Fo$*0264.exe $*02.asm
	asmc64 -q -peg -Fo$*0364.exe $*03.asm
	asmc64 -q $*04.asm
	linkw name $*0464 system gui_64 file $*04.obj
	asmc64 -q $*05.asm
	linkw name $*0564 system gui_64 file $*05.obj
	del *.obj
