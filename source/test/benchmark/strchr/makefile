#OBJDUMP = 1
LIBFILE = ../../../libc/string/_tcschr.asm

#all: strchr clean wcschr clean strchr64 clean wcschr64 clean

strchr:
	asmc -q -bin -arch:IA32 -Fo 1 $(LIBFILE)
	asmc -q -bin -arch:SSE	-Fo 2 $(LIBFILE)
	asmc -q -bin -arch:AVX	-Fo 3 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386 1.bin > 1_32.asm
	objdump -M intel -b binary -D -m i386 2.bin > 2_32.asm
	objdump -M intel -b binary -D -m i386 3.bin > 3_32.asm
endif
	asmc -q -pe timeit.asm
	timeit $@.txt
strchr64:
	asmc64 -q -bin -Fo 2 $(LIBFILE)
	asmc64 -q -bin -arch:AVX -Fo 3 $(LIBFILE)
	asmc64 -q -bin -arch:AVX512 -Fo 4 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64.asm
	objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64.asm
endif
	asmc64 -q -pe timeit.asm
	timeit $@.txt
wcschr:
	asmc -q -bin -ws -arch:IA32 -Fo 1 $(LIBFILE)
	asmc -q -bin -ws -arch:SSE	-Fo 2 $(LIBFILE)
	asmc -q -bin -ws -arch:AVX	-Fo 3 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386 1.bin > 1_32W.asm
	objdump -M intel -b binary -D -m i386 2.bin > 2_32W.asm
	objdump -M intel -b binary -D -m i386 3.bin > 3_32W.asm
endif
	asmc -q -pe -ws timeit.asm
	timeit $@.txt
wcschr64:
	asmc64 -q -bin -ws -Fo 2 $(LIBFILE)
	asmc64 -q -bin -ws -arch:AVX -Fo 3 $(LIBFILE)
	asmc64 -q -bin -ws -arch:AVX512 -Fo 4 $(LIBFILE)
ifdef OBJDUMP
	objdump -M intel -b binary -D -m i386:x86-64 2.bin > 2_64W.asm
	objdump -M intel -b binary -D -m i386:x86-64 3.bin > 3_64W.asm
	objdump -M intel -b binary -D -m i386:x86-64 4.bin > 4_64W.asm
endif
	asmc64 -q -pe -ws timeit.asm
	timeit $@.txt
clean:
	del *.bin
	del timeit.exe
