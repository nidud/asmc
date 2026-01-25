flags = -Zd
ifdef libc
flags += -MT
endif
static:
	asmc -elf $(flags) -Fo $@32 $@.asm
	asmc -elf64 $(flags) -Fo $@64 $@.asm
	@rm -f $@.o
clean:
	@rm -f static32
	@rm -f static64
debug32:
	gdb -x ../layout.gdb static32
debug64:
	gdb -x ../layout.gdb static64
