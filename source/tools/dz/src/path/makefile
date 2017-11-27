test.exe:
    asmc -pe $*.asm
    for %%q in (..\shared\*.asm) do $@ %%q
    pause

