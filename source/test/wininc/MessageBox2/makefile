test.exe:
    make -h -s WIN32A.exe
    make -h -s WIN32W.exe
    make -h -s WIN64A.exe
    make -h -s WIN64W.exe
    make -h -s WIN32APE.exe
    make -h -s WIN32WPE.exe
    make -h -s WIN64APE.exe
    make -h -s WIN64WPE.exe
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
    asmc -q -ws test.asm
    linkw system gui_32W name $@ file test
    $@
WIN64A.exe:
    echo $@
    asmc -q -win64 test.asm
    linkw system gui_64 name $@ file test
    $@
WIN64W.exe:
    echo $@
    asmc -q -win64 -ws test.asm
    linkw system gui_64W name $@ file test
    $@
WIN32APE.exe:
    echo $@
    asmc -q -pe -gui test.asm
    test.exe
WIN32WPE.exe:
    echo $@
    asmc -q -pe -gui -ws test.asm
    test.exe
WIN64APE.exe:
    echo $@
    asmc -q -pe -gui -D_WIN64 test.asm
    test.exe
WIN64WPE.exe:
    echo $@
    asmc -q -pe -gui -ws -D_WIN64 test.asm
    test.exe
