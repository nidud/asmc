
libdir = ..\..\lib\elf
lib_32 = $(libdir)\quadmath.lib
flags  = -elf -nolib

$(lib_32): directory
    asmc $(flags) -r const\*.asm x86\*.asm
    libw -q -b -n -c -ie $@ *.obj
    del *.obj

directory:
    if not exist $(libdir) md $(libdir)
