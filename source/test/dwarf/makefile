static:
	asmc64 -Zd -MT $@.asm
	gdb -x layout.gdb $@
	@rm -f $@.o
	@rm -f $@

static32:
	asmc -elf -Zd -MT -Fo $@ static.asm
	gdb -x layout.gdb $@
	@rm -f $@.o
	@rm -f $@
