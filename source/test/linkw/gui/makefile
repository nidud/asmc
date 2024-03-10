
all: gui_32 gui_64

gui_32:
	asmc -q -coff -Fo $@ gui.asm
	linkw system $@ file $@
	asmc -q -coff -ws -Fo $@W gui.asm
	linkw system $@W file $@W
	asmc -q -coff -Fo d$@ gui.asm
	linkw system d$@ file d$@
	asmc -q -coff -ws -Fo d$@W gui.asm
	linkw system d$@W file d$@W
gui_64:
	asmc64 -q -Fo $@ gui.asm
	linkw system $@ file $@
	asmc64 -q -ws -Fo $@W gui.asm
	linkw system $@W file $@W
	asmc64 -q -Fo d$@ gui.asm
	linkw system d$@ file d$@
	asmc64 -q -ws -Fo d$@W gui.asm
	linkw system d$@W file d$@W
clean:
	del *.obj
	del *.exe
