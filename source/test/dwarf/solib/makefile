solib:
	asmc64 -c -endbr -Zd main.asm -fPIC func2.asm $@.asm
	gcc -shared $@.o func2.o -o $@.so
	gcc main.o $@.so -o $@ -Wl,-rpath=.
	gdb -x ../layout.gdb ./$@
	@rm -f $@.o
	@rm -f $@
