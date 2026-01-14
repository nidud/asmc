dynamic:
	asmc64 -c -endbr -Zd main.asm -fPIC func?.asm
	gcc -shared func1.o func2.o -o $@.so
	gcc main.o $@.so -o $@ -Wl,-rpath=.
	gdb -x ../layout.gdb $@
	@rm -f *.o
	@rm -f $@.so
	@rm -f $@
