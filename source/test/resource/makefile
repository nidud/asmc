.SUFFIXES: .exe
.EXTENSIONS: .inc

OBJS =	icon.obj menu.obj cursor.obj dialog.obj string.obj
APPS =	icon.exe menu.exe cursor.exe dialog.exe string.exe control.exe unicode.exe bitmap.exe

{src}.asm.exe:
	asmc64 -q -Zp8 -ws -Cs -frame -peg $<
{res}.inc.obj:
	asmc64 -c -Fo $*res $<
	cl /GS- src\$*.cpp -link $*res.obj

build:	$(APPS)

link:	$(OBJS)

control.exe: wget.exe
	asmc64 -q -res res/$*.asm
	asmc64 -q -MD -Zp8 -ws -Cs -frame src/$*.asm -link -res:$*.res
bitmap.exe:
	asmc64 -q -res res/$*.asm
	asmc64 -q -MD -Zp8 -ws -Cs -frame src/$*.asm -link -res:$*.res
wget.exe:
	asmc64 -ws -pe res/wget.asm
	wget.exe

clean:
	del *.obj *.exe *.manifest *.res res\*.ico res\*.bmp res\*.avi

