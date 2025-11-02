
all: dz64 dz32

dz64:
	asmc64 -frame -Cs -Zp8 -MT -Fe$@ -Iinc src\*.asm
	del *.obj
dz32:
	asmc -8 -Cs -Zp4 -MT -Fe$@ -Iinc src\*.asm
	del *.obj

