builder:
	asmc64 -Zp8 -Cs -fpic builder.asm
	gcc -o builder builder.o `pkg-config --cflags --libs gtk4`

clean:
	rm builder.o
	rm builder
