tchar_test:
    make -h -s win32A.exe
    make -h -s win32W.exe
    make -h -s win32peA.exe
    make -h -s win32peW.exe
    make -h -s win64peA.exe
    make -h -s win64peW.exe
    del win*.exe

win32A.exe:
    asmc -q -Fo $*.obj test.asm
    linkw op q symt _cstart file $*
    $@ LINKW WIN32 ASCII
    del *.obj
    pause

win32W.exe:
    asmc -q -ws -D_UNICODE -Fo $*.obj test.asm
    linkw op q symt _wcstart file $*
    $@ LINKW WIN32 UNICODE
    del *.obj
    pause

win32peA.exe:
    asmc -q -pe -D__PE__ -Fo $*.exe test.asm
    $@ /pe WIN32 ASCII
    pause

win32peW.exe:
    asmc -q -pe -ws -D_UNICODE -D__PE__ -Fo $*.exe test.asm
    $@ /pe WIN32 UNICODE
    pause

win64peA.exe:
    asmc -q -pe -D_WIN64 -D__PE__ -Fo $*.exe test.asm
    $@ /pe WIN64 ASCII
    pause

win64peW.exe:
    asmc -q -pe -ws -D_WIN64 -D_UNICODE -D__PE__ -Fo $*.exe test.asm
    $@ /pe WIN64 UNICODE
    pause

