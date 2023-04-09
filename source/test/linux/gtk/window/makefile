window:
	asmc64 -Zp8 -Cs -fpic window.asm
	gcc -o window window.o `pkg-config --cflags --libs gtk4`

clean:
	rm window.o
	rm window
