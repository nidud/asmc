strsafe: strsafe.so
	asmc64 -c -fpic -endbr -Zd main.asm
	gcc main.o $@.so -o $@ -Wl,-rpath=.
	gdb -x ../layout.gdb ./$@
	@rm -f main.o
	@rm -f $@

strsafe.so:
	asmc64 -c -Zd -fPIC -Cs -D__DLL__ ../../../libs/strsafe/src/*.asm
	gcc -shared *.o -o $@
	rm *.o
