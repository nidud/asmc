test:
	../../../asmc -I../../../inc -elf64 test.asm
	../../../asmc -I../../../inc -elf64 iconfig.asm
	gcc -o test test.o iconfig.o
