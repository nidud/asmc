test.exe:
    asmc -q $*.asm
    linkw sys con_32 name A32$@ file $*
    A32$@
    asmc -q -ws $*.asm
    linkw sys con_32W name W32$@ file $*
    W32$@
    pause
    asmc64 -q $*.asm
    linkw sys con_64 name A64$@ file $*
    A64$@
    asmc64 -q -ws $*.asm
    linkw sys con_64W name W64$@ file $*
    W64$@
    del *.obj
    del *.exe
    pause
