
unicode = 1
bitness = 64

flags = -pe -gui -Cs
if $(unicode)
flags += -ws
endif
ifeq 64 $(bitness)
flags += -win64 -frame
endif

WicAnimatedGif.exe:
	asmc $(flags) $*.asm
	$@

