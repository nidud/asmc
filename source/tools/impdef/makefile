impdef.exe:
ifdef msvcrt
	asmc -pe $*.asm
else
	asmc $*.asm
	linkw name $@ system con_32 file $*.obj
endif
	pause
