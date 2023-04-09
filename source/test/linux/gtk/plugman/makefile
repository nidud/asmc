plugman:
	asmc64 -Zp8 -Cs -fpic plugman.asm
	gcc -o plugman plugman.o `pkg-config --cflags --libs gtk4`

clean:
	rm plugman.o
	rm plugman
