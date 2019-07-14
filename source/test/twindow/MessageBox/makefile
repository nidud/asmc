all: test.exe clean

test.exe:
    asmc64 -nologo $*.asm
    linkw sys tcon_64 file $*
    $@

clean:
    del *.obj
    del *.exe
