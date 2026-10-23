.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	heapwalk.exe \
	_aligned_malloc.exe \
	_aligned_msize.exe \
	_aligned_offset_malloc.exe \
	_aligned_rbp.exe \
	_msize.exe

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
