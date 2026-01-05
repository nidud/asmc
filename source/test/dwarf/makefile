dwarf:
	asmc64 -q -Zd $@.asm
	gdb -x layout.gdb ./$@
	@rm -f $@.o
	@rm -f $@
