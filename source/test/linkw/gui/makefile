
all: gui_32 gui_64

gui_32:
	asmc -c -q -coff -Fo $@ gui.asm
	linkw system $@ file $@
	asmc -c -q -coff -ws -Fo $@W gui.asm
	linkw system $@W file $@W
	asmc -c -q -coff -Fo d$@ gui.asm
	linkw system d$@ file d$@
	asmc -c -q -coff -ws -Fo d$@W gui.asm
	linkw system d$@W file d$@W
gui_64:
	asmc64 -q -Fo $@ gui.asm
	asmc64 -c -q -ws -Fo $@W gui.asm
	linkw system $@W file $@W
	asmc64 -c -q -Fo d$@ gui.asm
	linkw system d$@ file d$@
	asmc64 -c -q -ws -Fo d$@W gui.asm
	linkw system d$@W file d$@W
clean:
	del *.obj
	del *.exe
