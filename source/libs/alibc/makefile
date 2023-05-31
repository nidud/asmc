alibc.a:
	asmc64 -Zp8 -D_CRTBLD -Cs -r ../../libc/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp alibc.a /lib

