.SUFFIXES: .exe
.EXTENSIONS: .inc

OBJS =	icon.obj menu.obj cursor.obj dialog.obj string.obj
APPS =	icon.exe menu.exe cursor.exe dialog.exe string.exe control.exe

{src}.asm.exe:
	asmc64 -q -Zp8 -ws -Cs -frame -peg $<
{res}.inc.obj:
	asmc64 -c -Fo $*res $<
	cl /GS- src\$*.cpp -link $*res.obj

build:	$(APPS)

link:	$(OBJS)

clean:
	del *.obj *.exe *.manifest

