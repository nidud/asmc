
#OBJDUMP = 1

timeit:
        asmc -q -bin -D__TEST__ -Fo 1 ../../../libc/string/_tcslen.asm
        asmc -q -bin -D__TEST__ -arch:SSE -Fo 2 ../../../libc/string/_tcslen.asm
        asmc -q -bin -D__TEST__ -arch:AVX -Fo 3 ../../../libc/string/_tcslen.asm
        asmc -q -bin -arch:SSE -Fo 5 IntelSilvermont.asm
        asmc -q -bin -arch:SSE -Fo 6 IntelAtom.asm
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
        objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
        objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
        asmc -q -pe $@.asm
        $@
        asmc64 -q -bin -D__TEST__ -Fo 2 ../../../libc/string/_tcslen.asm
        asmc64 -q -bin -D__TEST__ -arch:AVX -Fo 3 ../../../libc/string/_tcslen.asm
        asmc64 -q -bin -D__TEST__ -arch:AVX512 -Fo 4 ../../../libc/string/_tcslen.asm
        asmc64 -q -bin -Fo 5 IntelSilvermont.asm
        asmc64 -q -bin -Fo 6 IntelAtom.asm
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64.asm
endif
        asmc64 -q -pe $@.asm
        $@
        del *.bin
        del $@.exe
        type result.txt
        pause
