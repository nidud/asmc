#
# Makefile for STRSAFE
#
ifdef YACC

strsafe.a:
	asmc -c -elf64 -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)
	asmc -c -elf -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)/x86

strsafe.so:
	asmc -c -elf64 -Cs -D__DLL__ src/*.asm
	gcc -shared *.o -o $@
	rm *.o

else

include srcpath

flags  = -BlLIBW -Cs -Z7
source = $(src_dir)\libs\strsafe\src
link   = -link -q -b -n -c -fac

strsafe.lib:
	asmc $(flags) -coff $(source)\*.asm -ws -Fo *W $(source)\*.asm $(link) $(lib_dir)\x86\$@
	asmc $(flags) -win64 -frame $(source)\*.asm -ws -Fo *W $(source)\*.asm $(link) $(lib_dir)\x64\$@
	del *.obj

strsafe.dll:
	asmc -q -win64 -frame -Cs $(source)\*.s -DCRTDLL -D_CRTBLD $(source)\*.asm -ws -Fo *W $(source)\*.asm -link -out:$@ -dll
	del *.obj

regress:
	asmc -q -win64 -frame -Cs $(source)\*.s -DCRTDLL -D_CRTBLD $(source)\*.asm -ws -Fo *W $(source)\*.asm -link -out:strsafe.dll -dll
	del *.obj
	asmc -q -win64 -pe -assert $(source)\strsafe.regress
	strsafe
	pause
	del strsafe.dll
	del strsafe.exe

endif