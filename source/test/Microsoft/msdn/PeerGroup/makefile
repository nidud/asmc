dynamic = 1

test.exe:
!if (dynamic)
	asmc64 -pe $*.asm
!else
	asmc64 $*.asm
!endif
	if exist $@ (
	  $@
	  pause
	)

