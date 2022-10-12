all: asmcalc.exe clean

asmcalc.exe:
    asmc64 -nologo -ws $*.asm
    linkw sys tcon_64W file $*
    $@

clean:
    del *.obj
#    del *.exe
