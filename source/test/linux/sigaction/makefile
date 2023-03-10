test:
	asmc64 -fpic test.asm
	gcc -o test test.o
	./test
	asmc64 -bin diasm.asm
	objdump -M intel -b binary -D -m i386:x86-64 diasm.bin

