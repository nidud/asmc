flags = -nologo -nolib
win32 = ../../lib/quadmath.lib
win64 = ../../lib/amd64/quadmath.lib
elf32 = ../../lib/elf/quadmath.lib

all: $(win32) $(win64) $(elf32)

base32 = \
    ../lib32/quadmath/*.asm \
    ../lib32/quadmath/const/*.asm \
    ../lib32/fltintrn/_strtoflt.asm \
    ../lib32/fltintrn/_fltsetflags.asm \
    ../lib32/fltintrn/_destoflt.asm \
    ../lib32/fltintrn/_fltscale.asm

base64 = \
    ../lib64/quadmath/*.asm \
    ../lib64/quadmath/const/*.asm \
    ../lib64/quadmath/fpu/*.asm \
    ../lib64/quadmath/xmm/*.asm \
    ../lib64/fltintrn/_strtoflt.asm \
    ../lib64/fltintrn/_fltsetflags.asm \
    ../lib64/fltintrn/_destoflt.asm \
    ../lib64/fltintrn/_fltscale.asm

$(win32):
    asmc $(flags) -Cs -coff -safeseh -Zi $(base32)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(win64):
    asmc $(flags) -Cs -win64 $(base64)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(elf32):
    if not exist ..\..\lib\elf md ..\..\lib\elf
    asmc -nologo -elf -nolib $(base32)
    libw -q -b -n -c -ie $@ *.obj
    del *.obj
