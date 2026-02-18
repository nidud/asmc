all: asmc clean

asmc:
	asmc64 -q -pe -Fo$@_pe $@.asm
	asmc64 -q -MD -Fo$@_md $@.asm
	asmc64 -q -MD -Bllink -Fo$@_ms $@.asm
	asmc -q -pe -Fo*_pe32 $@2.asm
	asmc -q -MD -coff -Fo*_md32 $@2.asm
	asmc64 -q -pe -Fo*_pe64 $@2.asm
	asmc64 -q -MD -Fo*_md64 $@2.asm
	$@_pe
	$@_md
	$@_ms
	$@2_pe32
	$@2_md32
	$@2_pe64
	$@2_md64
	@pause

clean:
	del *.exe
	del *.obj

vs:
	project -p asmc
