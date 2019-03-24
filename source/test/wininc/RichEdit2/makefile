test.exe:
    make -h -s WIN32APE.exe
    make -h -s WIN32WPE.exe
    make -h -s WIN64APE.exe
    make -h -s WIN64WPE.exe
    pause
WIN32APE.exe:
    echo $@
    asmc -q -pe -gui -Fo $@ test.asm
WIN32WPE.exe:
    echo $@
    asmc -q -pe -gui -ws -Fo $@ test.asm
WIN64APE.exe:
    echo $@
    asmc64 -q -pe -gui -Fo $@ test.asm
WIN64WPE.exe:
    echo $@
    asmc64 -q -pe -gui -ws -Fo $@ test.asm

