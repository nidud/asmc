got32_3: got32_3.so
	asmc -c -elf -fpic -Zd $@.asm
	gcc -m32 $@.o $@.so -o $@ -Wl,-rpath=.
	gdb -x ../layout.gdb $@
	@rm -f $@.o
	@rm -f $@.so
	@rm -f $@

got32_3.so:
	asmc -c -elf -Zd -fPIC -Cs -D__DLL__ func?.asm
	gcc -m32 -shared *.o -o $@
	rm *.o
