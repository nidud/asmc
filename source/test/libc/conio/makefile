.SUFFIXES: .obj .asm

.asm.obj:
	asmc64 -q -Cs -MT -Fe$*.exe $<

OBJS =	cgets.obj \
	getch.obj \
	message.obj \
	msgbox.obj \
	rcmove.obj \
	rcxchg.obj \
	rczip.obj \
	readinput.obj \
	rsopen.obj \
	syserr.obj \
	tcontrol.obj \
	terminal.obj \
	tgetline.obj

build:	$(OBJS)

rsopen.obj:
	asmc64 -q -Cs -MT -Fe$*.exe $*.asm -idd res/OpenFile.idd

clean:
ifdef YACC
	rm -f *.o *.exe *.s
else
	del *.obj *.exe *.s
endif
