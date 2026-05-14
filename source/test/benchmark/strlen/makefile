#OBJDUMP = 1
LIBFILE = ../../../libc/string/_tcslen.asm

#all: strlen clean strlen64 clean wcslen clean wcslen64 clean

strlen:
	asmc -q -bin -D__TEST__ -Fo 1 $(LIBFILE)
	asmc -q -bin -D__TEST__ -arch:SSE -Fo 2 $(LIBFILE)
	asmc -q -bin -D__TEST__ -arch:AVX -Fo 3 $(LIBFILE)
	asmc -q -bin -arch:SSE -Fo 5 IntelSilvermont.asm
	asmc -q -bin -arch:SSE -Fo 6 IntelAtom.asm
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
	objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
	objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
	asmc -q -pe timeit.asm
	timeit $@.txt
strlen64:
	asmc64 -q -bin -D__TEST__ -Fo 2 $(LIBFILE)
	asmc64 -q -bin -D__TEST__ -arch:AVX -Fo 3 $(LIBFILE)
	asmc64 -q -bin -D__TEST__ -arch:AVX512 -Fo 4 $(LIBFILE)
	asmc64 -q -bin -Fo 5 IntelSilvermont.asm
	asmc64 -q -bin -Fo 6 IntelAtom.asm
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64.asm
endif
	asmc64 -q -pe timeit.asm
	timeit $@.txt
wcslen:
	asmc -q -bin -ws -Fo 1 $(LIBFILE)
	asmc -q -bin -ws -arch:SSE -Fo 2 $(LIBFILE)
	asmc -q -bin -ws -arch:AVX -Fo 3 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
	objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
	objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
	asmc -q -pe -ws timeit.asm
	timeit $@.txt
wcslen64:
	asmc64 -q -bin -ws -Fo 2 $(LIBFILE)
	asmc64 -q -bin -ws -arch:AVX -Fo 3 $(LIBFILE)
	asmc64 -q -bin -ws -arch:AVX512 -Fo 4 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64.asm
endif
	asmc64 -q -pe -ws timeit.asm
	timeit $@.txt
clean:
	del *.bin
	del timeit.exe

