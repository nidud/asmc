test.exe:
    make -h -s WIN64APE.exe
    make -h -s WIN64WPE.exe
    del *.exe
    pause
WIN64APE.exe:
    echo $@
    asmc -q -pe -D_WIN64 test.asm
    test.exe
WIN64WPE.exe:
    echo $@
    asmc -q -pe -ws -D_WIN64 test.asm
    test.exe

