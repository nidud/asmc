pragma:
	for %%q in (t s c m l) do asmc -nologo -nolib -m%%q -1 $@.asm -link Name $@_%%q SYStem %%q File
	del $@.obj

