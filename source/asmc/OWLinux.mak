# Makefile for Asmc Linux using Open Watcom

watcom = \watcom

all: asmc asmc64

asmc:
	asmc -D__WATCOM__ -Isrc/inc -nologo -elf -nolib -Zp4 -Cs src\*.asm
	wlink @<<
name	asmc.
format	elf runtime linux
libpath $(watcom)/lib386
libpath $(watcom)/lib386/linux
lib	clib3s.lib
option	map, norelocs, quiet, stack=0x300000
file { *.obj }
<<
	del *.obj

asmc64:
	asmc -D__ASMC64__ -D__WATCOM__ -Isrc/inc -nologo -elf -nolib -Zp4 -Cs src\*.asm
	wlink @<<
name	asmc64.
format	elf runtime linux
libpath $(watcom)/lib386
libpath $(watcom)/lib386/linux
lib	clib3s.lib
option	norelocs, quiet, stack=0x300000
file { *.obj }
<<
	del *.obj
