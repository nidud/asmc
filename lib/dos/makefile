
libc:
	for %%q in (t s c m l) do asmc -q -m%%q -1 -D_CRTBLD -BlLIBW -r $@\*.asm -link $@%%q
	del *.obj
	for %%q in (t s c m l) do asmc -q -D_CRTBLD -m%%q -1 -Fo crt0%%q crt0.asm

