
all: con_32 con_64

con_32:
	asmc -q -Fo $@ console.asm
	linkw system $@ file $@
	asmc -q -ws -Fo $@W console.asm
	linkw system $@W file $@W
	asmc -q -Fo d$@ console.asm
	linkw system d$@ file d$@
	asmc -q -ws -Fo d$@W console.asm
	linkw system d$@W file d$@W
con_64:
	asmc64 -q -Fo $@ console.asm
	linkw system $@ file $@
	asmc64 -q -ws -Fo $@W console.asm
	linkw system $@W file $@W
	asmc64 -q -Fo d$@ console.asm
	linkw system d$@ file d$@
	asmc64 -q -ws -Fo d$@W console.asm
	linkw system d$@W file d$@W
clean:
	del *.obj
	del *.exe
