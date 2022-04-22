
../../../lib/libasmc.a:
	asmc64 -elf64 -nologo -Zp8 -D_CRTBLD -Cs -I../../../include -r *.asm
	ar rcs --target=elf64-x86-64 $@ *.o
	del *.o

