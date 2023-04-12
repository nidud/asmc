alibc.a:
	asmc64 -nologo -Zp8 -D_CRTBLD -Cs ../../libc/fltintrn/*.asm
	asmc64 -nologo -Zp8 -D_CRTBLD -Cs -r *.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp alibc.a /lib

