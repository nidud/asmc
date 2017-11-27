test.exe:
    make -h -s WIN32A.exe
    make -h -s WIN32W.exe
    make -h -s WIN64A.exe
    make -h -s WIN64W.exe
    del *.obj
    del *.exe
    pause

WIN32A.exe:
    echo $@
    asmc -q test.asm
    linkw system gui_32 name $@ file test
    $@
WIN32W.exe:
    echo $@
    asmc -q -ws -D_UNICODE test.asm
    linkw system gui_32W name $@ file test
    $@
WIN64A.exe:
    echo $@
    asmc -q -D_WIN64 test.asm
    linkw system gui_64 name $@ file test
    $@
WIN64W.exe:
    echo $@
    asmc -q -ws -D_WIN64 -D_UNICODE test.asm
    linkw system gui_64W name $@ file test
    $@
