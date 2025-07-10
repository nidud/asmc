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

pcg32.lib:
	asmc -BlLIBW -coff -Cs -r src\*.asm -link -q -b -n -c -fac $(lib_dir)\x86\$@
	asmc -BlLIBW -win6 -Cs -r src\*.asm -link -q -b -n -c -fac $(lib_dir)\x64\$@
	del *.obj

endif
