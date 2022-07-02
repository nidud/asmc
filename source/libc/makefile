!include srcpath

LIB32 = $(lib_dir)\x86\libc.lib
LIB64 = $(lib_dir)\x64\libc.lib

AFLAGS = -D_CRTBLD -Cs -Zi8 -I$(inc_dir)
LFLAGS = -q -b -n -c -fac

all: $(LIB32) $(LIB64)

$(LIB32):
    asmc $(AFLAGS) -coff -r $(src_dir)\libc\*.asm
    libw $(LFLAGS) $@ *.obj
    del *.obj

$(LIB64):
    asmc -win64 $(AFLAGS) -frame -Zp8 -r $(src_dir)\libc\*.asm
    libw $(LFLAGS) $@ *.obj
    del *.obj
