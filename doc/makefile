all: asmchm.exe clean

asmchm.exe:
	asmc64 -q -Cs $*.asm
	linkw system con_64 file $*
	$@
	hhc asmc.hhp
	del $*.obj

clean:
	del asmc.hhp
	del asmc.hhc
	del asmc.hhk
	del asmchm.exe
	del style.css
	del *.htm
	del error\*.htm
	del command\*.htm
	del symbol\*.htm
	del operator\*.htm
	del directive\*.htm
