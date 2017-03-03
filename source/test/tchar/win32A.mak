name	= test
cpp	= 1

!include master.mif
	$@ WIN32 ASCII
	pause
	del $*.exe
	del $*.obj
	del $*.map

