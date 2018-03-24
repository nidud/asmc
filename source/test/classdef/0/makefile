
test.exe:
    asmc -win64 *.asm
    libw -q -b class.lib class.obj
    linkw system con_64 lib class file test
    $@
    pause
    del *.obj
    del *.lib
