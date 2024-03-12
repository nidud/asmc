#
# Startup module for LIBC
#
ifdef YACC
argv:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	echo Press enter to continue; read dummy;
	rm $@.o
	rm $@
else
argv.exe:
	asmc -q $*.asm
	linkw system con_32 name A32$@ file $*
	A32$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc -q -ws $*.asm
	linkw system con_32W name W32$@ file $*
	W32$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc64 -q $*.asm
	linkw system con_64 name A64$@ file $*
	A64$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc64 -q -ws $*.asm
	linkw system con_64W name W64$@ file $*
	W64$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	del *.obj
	del *.exe
	pause
endif
