
all: import clean

import:
	ml64 -nologo $@0.asm -link -nologo
	ml64 -nologo $@1.asm -link -nologo
	asmc64 -pe $@0pe.asm
	asmc64 -pe $@1pe.asm
	$@0
	$@1
	$@0pe
	$@1pe
	@pause

clean:
#	del *.exe
	del *.obj
	del *.lnk

