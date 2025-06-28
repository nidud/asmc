
start:
	for %%q in (t s c m l) do asmc -q -Fe$@%%q -nolib -m%%q -1 $@.asm -link sys %%q f
	del $@.obj

