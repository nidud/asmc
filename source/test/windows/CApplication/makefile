flags = -ws -Zp8 -ws -Cs
ifdef x86
flags += -8 -coff
else
flags += -win64 -frame
endif

CApplication.exe:
	asmc $(flags) $*.asm
	$@
	del $@
	del $*.obj

vs:
	project -p -w -u CApplication
