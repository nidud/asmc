
dyn32:
	asmc -elf -fpic -Zd $@.asm
	gdb -x ../layout.gdb ./$@

clean:
	@rm -f dyn32.o
	@rm -f dyn32

