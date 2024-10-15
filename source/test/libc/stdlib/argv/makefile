#
# Startup module for LIBC
#
argv:
	asmc64 -q $@.asm
ifdef YACC
	./$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	@pause
	@rm $@.o
	@rm $@
else
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc64 -q -ws $@.asm
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc -q $@.asm
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	asmc -q -ws $@.asm
	$@ "4" 5 -7"quote" ""8" 9" "argv".asm
	pause
	del $@.obj
	del $@.exe
endif
