#OBJDUMP = 1
LIBFILE = ../../../libc/string/memcmp.asm

all: test32 test64 clean

test32:
        asmc -q -bin -D__TEST__ -arch:IA32 -Fo 1 $(LIBFILE)
        asmc -q -bin -D__TEST__ -arch:AVX  -Fo 2 $(LIBFILE)
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
        objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
endif
        asmc -q -pe timeit.asm
        timeit memcmp32.txt
test64:
        asmc64 -q -bin -D__TEST__ -Fo 1 $(LIBFILE)
        asmc64 -q -bin -D__TEST__ -arch:AVX -Fo 2 $(LIBFILE)
ifdef OBJDUMP
        objdump -M intel -b binary -D -m i386:x86-64 1.bin > 1_64.asm
        objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
endif
        asmc64 -q -pe timeit.asm
        timeit memcmp64.txt
clean:
        del *.bin
        del timeit.exe

