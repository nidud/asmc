all: test.exe clean

test.exe:
    asmc64 -ws -nologo $*.asm
    linkw sys tcon_64W file $*
    $@

clean:
    del *.obj
