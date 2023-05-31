#
# Test library for the Windows 10 Virtual Terminal
#
!include srcpath

L64 = $(lib_dir)\x64\libc.lib

flags = -D__TTY__ -D_CRTBLD -Cs -Zi8 -I$(inc_dir)

$(L64):
	asmc64 $(flags) -frame -Zp8 -r $(src_dir)\libc\*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
