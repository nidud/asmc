all: _msgbox clean

_msgbox:
	asmc64 ../../../../libc/conio/$@/$@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a

clean:
	./_msgbox
	rm _msgbox.o
	rm _msgbox
