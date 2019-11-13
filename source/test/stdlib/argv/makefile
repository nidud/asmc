test.exe:
    asmc -q $*.asm
    linkw system con_32 name A32$@ file $*
    A32$@ "4" 5 -7"quote" ""8" 9" "test".asm
    asmc -q -ws $*.asm
    linkw system con_32W name W32$@ file $*
    W32$@ "4" 5 -7"quote" ""8" 9" "test".asm
    asmc64 -q $*.asm
    linkw system con_64 name A64$@ file $*
    A64$@ "4" 5 -7"quote" ""8" 9" "test".asm
    asmc64 -q -ws $*.asm
    linkw system con_64W name W64$@ file $*
    W64$@ "4" 5 -7"quote" ""8" 9" "test".asm
    del *.obj
    del *.exe
    pause
