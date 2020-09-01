!include srcpath

AFLAGS	= -coff -Cs -Zi -I$(inc_dir)
LFLAGS	= -q -b -n -c -fac

$(lib_dir)\libc.lib:
	asmc $(AFLAGS) -r $(src_dir)\libs\lib32\*.asm
	libw $(LFLAGS) $@ *.obj
	del *.obj
