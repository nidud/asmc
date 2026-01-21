# Makefile for Linux auto link

auto:
	asmc -MT -elf -fno-pic -Fe $@_32. $@.asm
	asmc -MT -elf -fno-pic -DUSEFLT -Fe $@_32flt. $@.asm
	asmc -MT -elf64 -fno-pic -Fe $@_64. $@.asm
	asmc -MT -elf64 -fno-pic -DUSEFLT -Fe $@_64flt. $@.asm
	del $@.o

clean:
	del auto_*
