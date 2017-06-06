msgbox_test:
    make -h -s win32A.exe
    make -h -s win32W.exe
    make -h -s win64A.exe
    make -h -s win64W.exe
    make -h -s win32peA.exe
    make -h -s win32peW.exe
    make -h -s win64peA.exe
    make -h -s win64peW.exe
    del win*.exe
    del *.obj
    pause

win32A.exe:
    asmc -q -Fo $*.obj test.asm
    linkw op q symt _cstart file $*
    $@

win32W.exe:
    asmc -q -ws -D_UNICODE -Fo $*.obj test.asm
    linkw op q symt _wcstart file $*
    $@

win64A.exe:
    asmc -q -win64 -D_WIN64 -Fo $*.obj test.asm
    linkw op q symt cstart libpath \asmc\lib\x64 lib kernel32, user32, libc file $*
    $@

win64W.exe:
    asmc -q -win64 -D_WIN64 -ws -D_UNICODE -Fo $*.obj test.asm
    linkw op q symt wcstart libpath \asmc\lib\x64 lib kernel32, user32, libc file $*
    $@

win32peA.exe:
    asmc -q -pe -D__PE__ -Fo $*.exe test.asm
    $@

win32peW.exe:
    asmc -q -pe -ws -D_UNICODE -D__PE__ -Fo $*.exe test.asm
    $@

win64peA.exe:
    asmc -q -pe -D_WIN64 -D__PE__ -Fo $*.exe test.asm
    $@

win64peW.exe:
    asmc -q -pe -ws -D_WIN64 -D_UNICODE -D__PE__ -Fo $*.exe test.asm
    $@
