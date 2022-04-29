
CC = ../../../bin/asmc64
flags = -fpic -Zp8 -Cs -I../inc -I../../../include

all: asmc asmc64 clean

asmc:
	chmod u=rwx,go=r $(CC)
	$(CC) $(flags) ../x64/*.asm
	gcc -s -o $@ *.o

asmc64:
	$(CC) -DASMC64 $(flags) ../x64/*.asm
	gcc -s -o $@ *.o

clean:
	rm *.o

install:
	sudo install ./asmc /usr/local/bin
	sudo install ./asmc64 /usr/local/bin
