build:
    make -h -s hello_A32
    make -h -s hello_A64
    make -h -s hello_W32
    make -h -s hello_W64
    make -h -s hello_peA32
    make -h -s hello_peA64
    make -h -s hello_peW32
    make -h -s hello_peW64
    pause

hello_A32:
    asmc -q -Fo $*.obj hello.asm
    linkw sys con_32 file $*
hello_A64:
    asmc -q -Fo $*.obj -win64 hello.asm
    linkw sys con_64 file $*
hello_W32:
    asmc -q -Fo $*.obj -ws hello.asm
    linkw sys con_32W file $*
hello_W64:
    asmc -q -Fo $*.obj -win64 -ws hello.asm
    linkw sys con_64W file $*
    del *.obj

hello_peA32:
    asmc -q -pe -Fo $*.exe hello.asm
hello_peA64:
    asmc -q -pe -Fo $*.exe -win64 hello.asm
hello_peW32:
    asmc -q -pe -Fo $*.exe -ws hello.asm
hello_peW64:
    asmc -q -pe -Fo $*.exe -win64 -ws hello.asm
    dir *.exe | find ".exe"
