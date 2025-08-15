# Makefile for Linux auto link

auto:
	asmc -MT -elf -Fe $@_32. $@.asm
	asmc -MT -elf -DUSEFLT -Fe $@_32flt. $@.asm
	asmc -MT -elf64 -Fe $@_64. $@.asm
	asmc -MT -elf64 -DUSEFLT -Fe $@_64flt. $@.asm
	del $@.o

clean:
	del auto_*
