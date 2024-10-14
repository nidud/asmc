all: test.exe clean

test.exe:
    asmc64 -nologo $*.asm
    $@
    pause

clean:
    del *.obj
