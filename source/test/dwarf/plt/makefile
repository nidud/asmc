
all: plt clean

plt:
	asmc -Zd -elf -fplt -Fo $@32 $@.asm
	asmc -Zd -elf64 -fplt -Fo $@64 $@.asm

debug32:
	gdb -x ../layout.gdb plt32
debug64:
	gdb -x ../layout.gdb plt32
clean:
	@rm -f *.o
