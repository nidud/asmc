_rcmove:
	asmc64 -q -D__TTY__ $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause
ifdef YACC
	rm ./$@.o
	rm ./$@
else
	del $@.exe
	del $@.obj
endif

vs:
	project -p _rcmove

