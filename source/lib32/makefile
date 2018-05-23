!include srcpath

AFLAGS	= -coff -Cs -Zi -I$(inc_dir)
LFLAGS	= -q -b -n -c -fac

$(lib_dir)\libc.lib:
	asmc $(AFLAGS) $(src_dir)\quadmath\src\const\*.asm
	asmc $(AFLAGS) $(src_dir)\quadmath\src\x86\*.asm
	asmc $(AFLAGS) -r $(src_dir)\lib32\*.asm
	libw $(LFLAGS) $@ *.obj
	del *.obj
