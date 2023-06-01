all: _terminal clean

_terminal:
	asmc64 ../../../../libc/conio/$@/$@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a

clean:
	./_terminal
	rm _terminal.o
	rm _terminal
