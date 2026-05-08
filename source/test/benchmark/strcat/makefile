#OBJDUMP = 1
LIBFILE = ../../../libc/string/_tcscat.asm

all: test32 test64 clean

test32:
        asmc -q -bin -D__TEST__ -Fo 1 $(LIBFILE)
        asmc -q -bin -D__TEST__ -arch:SSE -Fo 2 $(LIBFILE)
        asmc -q -bin -D__TEST__ -arch:AVX -Fo 3 $(LIBFILE)
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
        objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
        objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
        asmc -q -pe timeit.asm
        timeit strcat32.txt
test64:
        asmc64 -q -bin -D__TEST__ -Fo 2 $(LIBFILE)
        asmc64 -q -bin -D__TEST__ -arch:AVX -Fo 3 $(LIBFILE)
        asmc64 -q -bin -D__TEST__ -arch:AVX512 -Fo 4 $(LIBFILE)
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64.asm
endif
        asmc64 -q -pe timeit.asm
        timeit strcat64.txt
clean:
        del *.bin
        del timeit.exe
