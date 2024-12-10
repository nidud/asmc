_tgetline:
	asmc64 -q -D__TTY__ $@.asm
ifdef YACC
	./$@
	rm $@.o
	tm $@
else
	$@
	del $@.exe
	del $@.obj
endif
