getenv:
	for %%q in (t s c m l) do asmc -q -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj
