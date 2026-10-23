.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	_BitScanForward.exe \
	_bittest.exe \
	_byteswap.exe \
	_InterlockedAnd.exe \
	_lrot.exe \
	_mul128.exe \
	_ReturnAddress.exe \
	__cpuid.exe \
	__emul.exe \
	__getcallerseflags.exe \
	__movsb.exe \
	__popcnt.exe \
	__rdtsc.exe \
	__rdtscp.exe \
	__segmentlimit.exe \
	__shiftleft128.exe \
	__stosb.exe \
	__ull_rshift.exe \
	zmmintrin.exe

build: $(targets)
ifdef YACC
	rm -f *.o
else
	del *.obj
endif

clean:
ifdef YACC
	rm -f *.exe *.o
else
	del *.exe *.obj
endif
