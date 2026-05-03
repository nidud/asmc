_rsopen:
	asmc64 -q -D__TTY__ $@.asm -idd res/OpenFile.idd
ifdef YACC
	./$@
else
	$@
endif
	@pause
ifdef YACC
	rm ./*.o
	rm ./$@
	rm OpenFile.s
else
	del $@.exe
	del *.obj
	del OpenFile.s
endif
