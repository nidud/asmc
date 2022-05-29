!include srcpath

AFLAGS = -Zi8 -frame -Zp8 -D_CRTBLD -Cs -I$(inc_dir)

$(lib_dir)\x64\twindow.lib:
    asmc64 $(AFLAGS) /r $(src_dir)\libs\twindow\source\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

