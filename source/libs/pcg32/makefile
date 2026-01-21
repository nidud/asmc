#
# Makefile for PCG32
#
ifdef YACC

apcg32.a:
	asmc -c -elf64 -fno-pic -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)
	asmc -c -elf -fno-pic -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ $(ASMCDIR)/x86

else

include srcpath

pcg32.lib:
	asmc -BlLIBW -coff -Cs -r $(src_dir)\libs\pcg32\src\*.asm -link -q -b -n -c -fac $(lib_dir)\x86\$@
	asmc -BlLIBW -win6 -Cs -r $(src_dir)\libs\pcg32\src\*.asm -link -q -b -n -c -fac $(lib_dir)\x64\$@
	del *.obj

endif
