#
# Startup module for LIBC
#
ifdef YACC
argv:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	echo Press enter to continue; read dummy;
	rm $@.o
	rm $@
else
argv.exe:
	asmc -c -q $*.asm -link
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc -c -q -ws $*.asm -link
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc64 -c -q $*.asm -link
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc64 -c -q -ws $*.asm -link
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	del $*.obj
	del $*.exe
	pause
endif
