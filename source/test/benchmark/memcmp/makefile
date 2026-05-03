#OBJDUMP = 1

time32:
    asmc -q -bin -D__TEST__ -Fo 1 ../../../libc/string/memcmp.asm
    asmc -q -bin -D__TEST__ -arch:AVX  -Fo 2 ../../../libc/string/memcmp.asm
ifdef OBJDUMP
    objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
    objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
endif
    asmc -q -pe timeit.asm
    timeit
    asmc64 -q -bin -D__TEST__ -Fo 1 ../../../libc/string/memcmp.asm
    asmc64 -q -bin -D__TEST__ -arch:AVX -Fo 2 ../../../libc/string/memcmp.asm
ifdef OBJDUMP
    objdump -M intel -b binary -D -m i386:x86-64 1.bin > 1_64.asm
    objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
endif
    asmc64 -q -pe timeit.asm
    timeit
    del *.bin
    del timeit.exe
    type result.txt
    pause
