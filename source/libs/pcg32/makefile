#
# Makefile for [A]PCG32
#
ifdef YACC

apcg32.a:
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

all: $(lib_dir)/x64/pcg32.lib $(lib_dir)/x86/pcg32.lib

$(lib_dir)/x86/pcg32.lib:
	asmc -c -coff -Cs src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

$(lib_dir)/x64/pcg32.lib:
	asmc64 -c -Cs src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

endif
