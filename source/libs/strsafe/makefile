#
# Makefile for STRSAFE
#
ifdef YACC

strsafe.a:
	asmc64 -c -fpic -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)
	asmc -c -elf -fpic -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)/x86

else

include srcpath

strsafe.lib:
	asmc -BlLIBW -coff -Cs -Zi src\*.asm -ws -Fo *W src\*.asm -link -q -b -n -c -fac $(lib_dir)\x86\$@
	asmc -BlLIBW -win64 -Cs -Zi -frame src\*.asm -ws -Fo *W src\*.asm -link -q -b -n -c -fac $(lib_dir)\x64\$@
	del *.obj

strsafe.dll:
	asmc64 -q -frame -Cs src\*.s -DCRTDLL -D_CRTBLD src\*.asm -ws -Fo *W src\*.asm -link -out:$@ -dll
	del *.obj

regress:
	make -h -s strsafe.dll
	asmc64 -q -pe -assert strsafe.regress
	strsafe
	pause
	del strsafe.dll
	del strsafe.exe

endif
