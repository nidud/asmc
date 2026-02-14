# Makefile for asmc Sat Feb 14 2026

asmc:
	asmc64 -q -pe -Fo$@_pe $@.asm
	asmc64 -q -MD -Fo$@_md $@.asm
	$@_pe
	$@_md
	@pause

clean:
	del *.exe
	del *.obj

vs:
	project -p asmc
