action:
	asmc64 -Zp8 -Cs -fpic action.asm
	gcc -o action action.o `pkg-config --cflags --libs gtk4`

clean:
	rm action.o
	rm action
