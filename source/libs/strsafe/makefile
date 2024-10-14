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

all: $(lib_dir)/x86/strsafe.lib $(lib_dir)/x64/strsafe.lib

$(lib_dir)/x86/strsafe.lib:
	asmc -c -coff -Cs -Z7 src/*.asm
	asmc -c -coff -Cs -Z7 -ws -Fo *W src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

$(lib_dir)/x64/strsafe.lib:
	asmc64 -c -frame -Cs -Z7 src/*.asm
	asmc64 -c -frame -Cs -Z7 -ws -Fo *W src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

strsafe.dll:
	asmc64 -c -q -frame -Cs -Z7 src/*.s
	asmc64 -c -q -frame -Cs -Z7 -DCRTDLL -D_CRTBLD src/*.asm
	asmc64 -c -q -frame -Cs -Z7 -DCRTDLL -D_CRTBLD -ws -Fo *W src/*.asm
	linkw op q name strsafe.dll sys dll_64 file { *.obj }
	del *.obj

regress:
	make -h -s strsafe.dll
	asmc64 -q -pe -assert strsafe.regress
	strsafe
	pause

endif