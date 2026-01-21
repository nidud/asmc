pause:
ifdef YACC
	asmc64 -q -fno-pic -Bl /usr/bin/ld $@.asm -link -s -o $@
else
	asmc -Fe$@. -elf64 -fno-pic $@.asm
endif

clean:
	rm -f ./pause.o
	rm -f ./pause

install:
	sudo install ./pause /usr/bin

