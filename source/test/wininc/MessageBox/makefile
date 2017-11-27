test.exe:
    make -h -s WIN32PEA.exe
    make -h -s WIN32PEW.exe
    make -h -s WIN64PEA.exe
    make -h -s WIN64PEW.exe
    del *.exe
    pause

WIN32PEA.exe:
    echo $@
    asmc -q -pe -Fo $@ test.asm
    $@
WIN32PEW.exe:
    echo $@
    asmc -q -pe -ws -D_UNICODE -Fo $@ test.asm
    $@
WIN64PEA.exe:
    echo $@
    asmc -q -pe -D_WIN64 -Fo $@ test.asm
    $@
WIN64PEW.exe:
    echo $@
    asmc -q -pe -ws -D_WIN64 -D_UNICODE -Fo $@ test.asm
    $@
