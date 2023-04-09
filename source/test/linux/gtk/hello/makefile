hello:
	asmc64 -Zp8 -Cs -fpic hello.asm
	gcc -o hello hello.o `pkg-config --cflags --libs gtk4`

clean:
	rm hello.o
	rm hello
