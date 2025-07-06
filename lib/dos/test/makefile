
model:
	for %%q in (t s c m l h) do asmc -q -c -m%%q -1 $@.asm
	pause
	del *.obj

start:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

argv:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

dostime:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

fopen:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

formatb:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

getenv:
	for %%q in (t s c m l) do asmc -q -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

pragma:
	for %%q in (t s c m l) do asmc -nologo -Fe$@%%q -m%%q -1 $@.asm
	del $@.obj

clean:
	del *.exe
