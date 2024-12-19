
unicode = 1
bitness = 64

ifeq 64 $(bitness)
flags = -win64 -frame
else
flags = -8
endif
if $(unicode)
flags += -ws
endif
flags += -peg -Cs

WicAnimatedGif.exe:
	asmc $(flags) $*.asm
	$@

