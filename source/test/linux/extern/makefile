test:
	../../asmc -I../../inc -elf64 test.asm
	../../asmc -I../../inc -elf64 getstring.asm
	gcc -o test test.o getstring.o
