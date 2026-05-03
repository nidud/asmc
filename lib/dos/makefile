all: libc crt0

libc:
	for %%q in (t s c m l) do asmc -q -m%%q -1 -MT -BlLIBW -r $@\*.asm -link $@%%q.lib
	del *.obj

crt0:
	for %%q in (t s c m l) do asmc -q -D_CRTBLD -m%%q -1 -Fo $@%%q $@.asm

