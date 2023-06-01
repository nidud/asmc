all: cout stdio clean

cout:
	asmc64 ../../../../libc/iostream/$@/*.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a

stdio:
	gcc -nostdlib -o stdio stdio.o /lib/alibc.a

clean:
	./cout
	./stdio
	rm *.o
	rm cout
	rm stdio
	read "Press any key to continue..."