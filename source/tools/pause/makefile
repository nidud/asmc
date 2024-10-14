ifdef YACC

aflags = -c -q -Cs -fpic
lflags = -nostdlib -Wl,-pie,-z,now,-z,noexecstack

pause:
	asmc64 $(aflags) $@.asm
	gcc -s -o $@ $@.o $(lflags)

clean:
	rm -f *.o
	rm -f ./pause

install:
	sudo install ./pause /usr/bin

endif
