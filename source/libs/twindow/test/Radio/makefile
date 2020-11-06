all: test.exe clean

test.exe:
    asmc64 -nologo $*.asm
    iddc -win64 Replace.IDD
    linkw sys tcon_64 file $*, Replace
    $@

clean:
    del *.obj
    del *.exe
