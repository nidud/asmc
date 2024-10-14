ifdef YACC
format_b:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
format_b.exe:
	asmc -c -q $*.asm
	linkw sys con_32 name A32$@ file $*
	A32$@
	asmc -c -q -ws $*.asm
	linkw sys con_32W name W32$@ file $*
	W32$@
	pause
	asmc64 -c -q $*.asm
	linkw sys con_64 name A64$@ file $*
	A64$@
	asmc64 -c -q -ws $*.asm
	linkw sys con_64W name W64$@ file $*
	W64$@
	pause
	del *.obj
	del *.exe
endif