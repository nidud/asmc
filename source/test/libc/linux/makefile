.SUFFIXES: .obj .asm

.asm.obj:
	asmc64 -q -Cs -MT -Fe$*.exe $<

OBJS =	localtime.obj \
	systemtime.obj \
	widechar.obj \
	searchpath.obj \
	memory.obj \
	clipboard.obj

build:	$(OBJS)

clean:
	rm -f *.o *.exe
