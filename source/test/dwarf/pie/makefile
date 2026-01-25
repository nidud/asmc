all: pie32 pie64

pie32: lib32
	asmc -c -elf -fPIC -Zd main.asm
	gcc -m32 main.o lib32.so -o $@ -Wl,-rpath=.
	@rm -f main.o
pie64: lib64
	asmc -c -elf64 -fPIC -Zd main.asm
	gcc main.o lib64.so -o $@ -Wl,-rpath=.
	@rm -f main.o
lib32:
	asmc -c -elf -fPIC -Zd -D__DLL__ func?.asm
	gcc -m32 -shared *.o -o $@.so
	@rm -f *.o
lib64:
	asmc -c -elf64 -fPIC -Zd -D__DLL__ func?.asm
	gcc -shared *.o -o $@.so
	@rm -f *.o
clean:
	@rm -f pie32
	@rm -f lib32.so
	@rm -f pie64
	@rm -f lib64.so
debug32:
	gdb -x ../layout.gdb pie32
debug64:
	gdb -x ../layout.gdb pie64
