build:
    make -h -s test_A32
    make -h -s test_A64
    make -h -s test_W32
    make -h -s test_W64
    make -h -s test_peA32
    make -h -s test_peA64
    make -h -s test_peW32
    make -h -s test_peW64
    pause

test_A32:
    asmc -q -Fo $*.obj test.asm
    linkw sys gui_32 file $*
test_A64:
    asmc -q -Fo $*.obj -win64 test.asm
    linkw sys gui_64 file $*
test_W32:
    asmc -q -Fo $*.obj -ws test.asm
    linkw sys gui_32W file $*
test_W64:
    asmc -q -Fo $*.obj -win64 -ws test.asm
    linkw sys gui_64W file $*
    del *.obj

test_peA32:
    asmc -q -pe -gui -Fo $@.exe test.asm
test_peA64:
    asmc -q -pe -gui -Fo $@.exe -win64 test.asm
test_peW32:
    asmc -q -pe -gui -Fo $@.exe -ws test.asm
test_peW64:
    asmc -q -pe -gui -Fo $@.exe -win64 -ws test.asm
    dir *.exe | find ".exe"
