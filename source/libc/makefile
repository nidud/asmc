!include srcpath

L32 = $(lib_dir)\x86\libc.lib
L64 = $(lib_dir)\x64\libc.lib

flags = -D_CRTBLD -Cs -Zi8 -I$(inc_dir)

all: $(L32) $(L64)

$(L32):
	asmc $(flags) -6 -coff -r $(src_dir)\libc\*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

$(L64):
	asmc -win64 $(flags) -frame -Zp8 -r $(src_dir)\libc\*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
