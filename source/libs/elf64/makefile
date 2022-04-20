
../../../lib/libasmc.a:
        asmc -nologo -elf64 -Zp8 -D_CRTBLD -Cs -I../../../include -r *.asm
        ar rcs --target=elf64-x86-64 $@ *.o
        del *.o

