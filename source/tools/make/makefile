#
# Makefile for MAKE
#
make.exe:
ifdef x86
	asmc -pe -Cs $*.asm
else
	asmc64 -pe -Cs -frame $*.asm
endif

