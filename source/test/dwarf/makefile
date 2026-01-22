static:
	asmc64 -Zd $@.asm
	gdb -x layout.gdb $@
	@rm -f $@.o
	@rm -f $@

static32:
	asmc -elf -Zd -Fo $@ static.asm
	gdb -x layout.gdb $@
	@rm -f $@.o
	@rm -f $@
