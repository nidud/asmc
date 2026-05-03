pause:
ifdef YACC
	asmc64 -q -Bl /usr/bin/ld $@.asm -link -s -o $@
else
	asmc -Fe$@. -elf64 $@.asm
endif

clean:
	rm -f ./pause.o
	rm -f ./pause

install:
	sudo install ./pause /usr/bin

