signal:
	asmc64 -fpic signal.asm
	gcc -o signal signal.o
	./test
	asmc64 -bin diasm.asm
	objdump -M intel -b binary -D -m i386:x86-64 diasm.bin

