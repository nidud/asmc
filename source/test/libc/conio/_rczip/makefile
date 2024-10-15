ifdef YACC
_rczip:
	asmc64 $@.asm
	./$@
	rm -f $@.o
	rm -f $@
else
_rczip.exe:
	asmc64 -c -q $*.asm
	linkw system tty_64 file $*
	$@
	del *.obj
	del *.exe
endif
