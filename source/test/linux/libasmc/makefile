test:
	asmc64 -I../../../../include *.asm
	gcc -o hello hello.o /lib/libasmc.a
	gcc -o cout cout.o /lib/libasmc.a
	gcc -o printf printf.o /lib/libasmc.a
	gcc -o fopen fopen.o /lib/libasmc.a
	gcc -o isatty isatty.o /lib/libasmc.a
	gcc -o float float.o /lib/libasmc.a

clean:
	rm *.o
	rm ./hello
	rm ./cout
	rm ./printf
	rm ./fopen
	rm ./isatty
	rm ./float
