_rsopen:
	asmc64 -q $@.asm -idd res/OpenFile.idd
ifdef YACC
	./$@
	rm *.o
	rm *.s
	rm $@
else
	$@
	del *.obj
	del *.s
	del $@.exe
endif
