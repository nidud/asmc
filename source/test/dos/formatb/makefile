formatb:
	for %%q in (t s c m l) do asmc -nologo -nolib -m%%q -1 $@.asm -link N $@%%q SYS %%q F
	del $@.obj

