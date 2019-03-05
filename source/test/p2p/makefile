dynamic = 1

test.exe:
!if (dynamic)
	asmc64 -pe $*.asm
!else
	asmc64 $*.asm
	linkw sys con_64 file $*
!endif
	if exist $@ (

	  $@
	  pause
	)

