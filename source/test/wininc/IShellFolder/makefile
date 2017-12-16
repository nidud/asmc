test.exe: test_pe32 test_pe64
    asmc -win64 -Zp8 $*.asm
    linkw system con_64 file $*
    $@
    pause
    del $@
    del $*.obj

test_pe32:
    asmc -pe -Zp4 -Fo test_pe32.exe test.asm

test_pe64:
    asmc -pe -Zp8 -Fo test_pe64.exe test.asm
