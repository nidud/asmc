!include srcpath

TWINA = $(lib_dir)\x64\TWinA.lib
TWINW = $(lib_dir)\x64\TWinW.lib

AFLAGS = -Zi8 -frame -Zp8 -D_CRTBLD -Cs -I$(inc_dir)

all: $(TWINA) $(TWINW)

$(TWINA):
    asmc64 $(AFLAGS) /r $(src_dir)\libs\twindow\source\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(TWINW):
    asmc64 -ws $(AFLAGS) /r $(src_dir)\libs\twindow\source\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

