all: test.exe clean

test.exe:
    asmc64 -nologo $*.asm
    iddc -win64 ..\..\..\tools\dz\res\idd\EditColor.IDD
    linkw sys tcon_64 file $*, EditColor
    $@

clean:
    del *.obj
    del *.exe
