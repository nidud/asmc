# Makefile for Asmc Linux using Open Watcom

watcom = \watcom

all: asmc asmc64

asmc:
	asmc -D__WATCOM__ -Iinc -nologo -elf -nolib -Zp4 -Cs src\*.asm
	linkw @<<
name	asmc.
format	elf runtime linux
libpath $(watcom)\lib386\linux
lib	clib3s.lib
file { *.o }
<<
	del *.o

asmc64:
	asmc -DASMC64 -D__WATCOM__ -Iinc -nologo -elf -nolib -Zp4 -Cs src\*.asm
	linkw @<<
name	asmc64.
format	elf runtime linux
libpath $(watcom)\lib386\linux
lib	clib3s.lib
file { *.o }
<<
	del *.o
