#OBJDUMP = 1

timeit:
        asmc -q -bin -D__TEST__ -ws -Fo 1 ../../../libc/string/_tcscpy.asm
        asmc -q -bin -D__TEST__ -ws -arch:SSE -Fo 2 ../../../libc/string/_tcscpy.asm
        asmc -q -bin -D__TEST__ -ws -arch:AVX -Fo 3 ../../../libc/string/_tcscpy.asm
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
        objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
        objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
        asmc -q -pe $@.asm
        del result.txt
        $@
        asmc64 -q -bin -D__TEST__ -ws -Fo 2 ../../../libc/string/_tcscpy.asm
        asmc64 -q -bin -D__TEST__ -ws -arch:AVX -Fo 3 ../../../libc/string/_tcscpy.asm
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
endif
        asmc64 -q -pe $@.asm
        $@
        del *.bin
        del $@.exe
        type result.txt
        pause
