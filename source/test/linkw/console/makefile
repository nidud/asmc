
all: con_32 con_64

con_32:
	asmc -c -q -Fo $@ console.asm
	linkw system $@ file $@
	asmc -c -q -ws -Fo $@W console.asm
	linkw system $@W file $@W
	asmc -c -q -Fo d$@ console.asm
	linkw system d$@ file d$@
	asmc -c -q -ws -Fo d$@W console.asm
	linkw system d$@W file d$@W
con_64:
	asmc64 -c -q -Fo $@ console.asm
	linkw system $@ file $@
	asmc64 -c -q -ws -Fo $@W console.asm
	linkw system $@W file $@W
	asmc64 -c -q -Fo d$@ console.asm
	linkw system d$@ file d$@
	asmc64 -c -q -ws -Fo d$@W console.asm
	linkw system d$@W file d$@W
clean:
	del *.obj
	del *.exe
