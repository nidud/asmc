
start:
	for %%q in (t s c m l) do asmc -q -nolib -m%%q -1 $@.asm -link N $@_%%q sys %%q f
	del $@.obj

