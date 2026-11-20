.SUFFIXES: .obj .asm

.asm.obj:
	asmc64 -q -Cs -MT -Fe$*.exe $<

OBJS =	localtime.obj systemtime.obj

build:	$(OBJS)

clean:
	rm -f *.o* *.exe
