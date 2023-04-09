search:
	asmc64 -Zp8 -Cs -fpic search.asm
	gcc -o search search.o `pkg-config --cflags --libs gtk4`

clean:
	rm search.o
	rm search
