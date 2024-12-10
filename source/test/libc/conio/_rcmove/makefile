_rcmove:
	asmc -q -D__TTY__ $@.asm
ifdef YACC
	./$@
	rm -f $@.o
	rm -f $@
else
	$@
	del *.obj
	del *.exe
endif
