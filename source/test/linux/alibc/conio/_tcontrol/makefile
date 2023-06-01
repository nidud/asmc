all: _tcontrol clean

_tcontrol:
	asmc64 ../../../../libc/conio/$@/$@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a

clean:
	./_tcontrol
	rm _tcontrol.o
	rm _tcontrol
