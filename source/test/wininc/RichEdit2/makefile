test.exe:
    make -h -s WIN32APE.exe
    make -h -s WIN32WPE.exe
    make -h -s WIN64APE.exe
    make -h -s WIN64WPE.exe
    del *.exe
    pause
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

