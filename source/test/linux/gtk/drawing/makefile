drawing:
	asmc64 -Zp8 -Cs -fpic drawing.asm
	gcc -o drawing drawing.o `pkg-config --cflags --libs gtk4`

clean:
	rm drawing.o
	rm drawing
