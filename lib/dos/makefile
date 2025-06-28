
libc:
	for %%q in (t s c m l) do asmc -m%%q -Fe$@%%q -q -1 -D_CRTBLD -BlLIBW -r $@\*.asm
	del *.obj
	for %%q in (t s c m l) do asmc -q -D_CRTBLD -m%%q -1 -Fo _start%%q $@\crt\_start.s

