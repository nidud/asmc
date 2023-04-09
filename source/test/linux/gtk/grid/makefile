grid:
	asmc64 -Zp8 -Cs -fpic grid.asm
	gcc -o grid grid.o `pkg-config --cflags --libs gtk4`

clean:
	rm grid.o
	rm grid
