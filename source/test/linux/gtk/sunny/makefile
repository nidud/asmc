sunny:
	asmc64 -Zp8 -Cs -fpic sunny.asm
	gcc -o sunny sunny.o `pkg-config --cflags --libs gtk4`

clean:
	rm sunny.o
	rm sunny
