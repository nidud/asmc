model:
	asmc -q -c -mt -Fo tiny $*.asm
	asmc -q -c -ms -Fo small $*.asm
	asmc -q -c -mc -Fo compact $*.asm
	asmc -q -c -mm -Fo medium $*.asm
	asmc -q -c -ml -Fo large $*.asm
	asmc -q -c -mh -Fo huge $*.asm
	asmc -q -c -mf -Fo flat $*.asm
	pause
	del *.obj

