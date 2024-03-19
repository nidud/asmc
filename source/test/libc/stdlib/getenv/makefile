ifdef YACC

getenv:
	asmc -fpic -elf64 $@.asm
	gcc -nostdlib -o $@64 $@.o -l:libasmc.a -Wl,-Map $@64.map
	asmc -fpic -elf $@.asm
	gcc -static -m32 -nostdlib -o $@32 $@.o -l:x86/libasmc.a -Wl,-Map $@32.map
clean:
	rm *.o
	rm *.map
	rm ./getenv32
	rm ./getenv64
else

getenv.exe:
	asmc -q $*.asm
	linkw sys con_32 name A32$@ file $*
	A32$@
	asmc -q -ws $*.asm
	linkw sys con_32W name W32$@ file $*
	W32$@
	asmc64 -q $*.asm
	linkw sys con_64 name A64$@ file $*
	A64$@
	asmc64 -q -ws $*.asm
	linkw sys con_64W name W64$@ file $*
	W64$@
	pause
	del *.obj
	del *.exe
endif