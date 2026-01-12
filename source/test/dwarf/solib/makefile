solib:
	asmc64 -c -endbr -Zd main.asm -fPIC $@.asm
	gcc -shared $@.o -o $@.so
	gcc main.o $@.so -o $@ -Wl,-rpath=.
	gdb -x ../layout.gdb ./$@
	@rm -f $@.o
	@rm -f $@
