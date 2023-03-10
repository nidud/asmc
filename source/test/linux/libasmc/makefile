test:
	asmc64 *.asm
	gcc -nostdlib -o hello hello.o /lib/libasmc.a
	gcc -nostdlib -o cout cout.o /lib/libasmc.a
	gcc -nostdlib -o printf printf.o /lib/libasmc.a
	gcc -nostdlib -o fopen fopen.o /lib/libasmc.a
	gcc -nostdlib -o isatty isatty.o /lib/libasmc.a
	gcc -nostdlib -o float float.o /lib/libasmc.a
	gcc -nostdlib -o imagerel imagerel.o /lib/libasmc.a
	gcc -nostdlib -o pragma pragma.o /lib/libasmc.a -Wl,-Map,pragma.map

clean:
	rm *.o
	rm hello
	rm cout
	rm printf
	rm fopen
	rm isatty
	rm float
	rm imagerel
	rm pragma
