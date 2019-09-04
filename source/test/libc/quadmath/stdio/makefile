all: win32 win64 clean

clean:
    del *.obj
    del *.exe
    pause
win32:
    asmc -q test.asm
    linkw system con_32 name $@ file test
    $@
win64:
    asmc64 -q test.asm
    linkw system con_64 name $@ file test
    $@
