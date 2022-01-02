!include srcpath

AFLAGS	= -coff -Cs -Zi -I$(inc_dir)
LFLAGS	= -q -b -n -c -fac

target_path = $(lib_dir)\x86

$(target_path)\libc.lib: $(target_path)
	asmc $(AFLAGS) -r $(src_dir)\libs\lib32\*.asm
	libw $(LFLAGS) $@ *.obj
	del *.obj

$(target_path):
    if not exist $(target_path) md $(target_path)
