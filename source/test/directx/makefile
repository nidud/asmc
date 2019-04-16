all: test.exe clean

test.exe:
    asmc64 -nologo $*.asm
    linkw sys con_64 file $*
    $@
    pause

clean:
    del *.obj
    del *.exe
