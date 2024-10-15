_aligned_offset_malloc:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm $@.o
	@rm $@
else
	$@
	pause
	del $*.obj
	del $*.exe
endif
