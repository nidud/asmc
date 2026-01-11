foo:
	asmc64 -c -endbr -Zd *.asm
	gcc -shared bar.o -o bar.so
	gcc foo.o bar.so -o foo -Wl,-rpath=.
	gdb -x ../layout.gdb ./$@
	@rm -f *.o
	@rm -f bar.so
	@rm -f $@
