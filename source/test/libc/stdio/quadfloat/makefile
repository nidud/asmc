test.exe:
    make -h -s WIN32A.exe
    make -h -s WIN64A.exe
    del *.obj
    del *.exe
    pause
WIN32A.exe:
    echo $@
    asmc -q test.asm
    linkw system con_32 name $@ file test
    $@
WIN64A.exe:
    echo $@
    asmc -q -D_WIN64 test.asm
    linkw system con_64 name $@ file test
    $@
