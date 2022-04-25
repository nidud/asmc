libasmc.a:
	asmc64 -nologo -Zp8 -D_CRTBLD -Cs -I../../../include -r *.asm
	ar rcs $@ *.o
	rm *.o
	sudo install ./libasmc.a /lib

