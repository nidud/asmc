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
    asmc -q test.asm
    linkw name $@ system gui_32 file test
    $@

win32W.exe:
    asmc -q -ws -D_UNICODE -Fo $*.obj test.asm
    linkw system gui_32W file $*
    $@

win64A.exe:
    asmc -q -win64 -D_WIN64 -Fo $*.obj test.asm
    linkw system gui_64 file $*
    $@

win64W.exe:
    asmc -q -win64 -D_WIN64 -ws -D_UNICODE -Fo $*.obj test.asm
    linkw system gui_64W file $*
    $@

win32peA.exe:
    asmc -q -pe -D__GUI__ -Fo $*.exe test.asm
    $@

win32peW.exe:
    asmc -q -pe -ws -D_UNICODE -D__GUI__ -Fo $*.exe test.asm
    $@

win64peA.exe:
    asmc -q -pe -D_WIN64 -D__GUI__ -Fo $*.exe test.asm
    $@

win64peW.exe:
    asmc -q -pe -ws -D_WIN64 -D_UNICODE -D__GUI__ -Fo $*.exe test.asm
    $@
