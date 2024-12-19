pause:
	asmc64 -q -Bl /usr/bin/ld $@.asm -link -s -o $@

clean:
	rm -f ./pause.o
	rm -f ./pause

install:
	sudo install ./pause /usr/bin

