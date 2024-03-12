ifdef YACC

getenv:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@64 $@.o -l:libasmc.a -Wl,-Map $@64.map
	asmc -fpic -elf $@.asm
	gcc -nostdlib -m32 -o $@32 $@.o -l:x86/libasmc.a -Wl,-Map $@32.map

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