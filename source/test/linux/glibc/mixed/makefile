mixed:
	asmc64 -fpic ../../../libc/$@/$@.asm
	gcc -c ../../../libc/$@/main.cpp
	gcc -o $@ main.o $@.o

