
test:
	asmc -Fo __ImageBase_ASMC_32 -pe $@.asm
	asmc -Fo __ImageBase_LINK_32 -nolib -coff -Bl link $@.asm
	asmc -win64 -Fo __ImageBase_ASMC_64 -pe $@.asm
	asmc -win64 -Fo __ImageBase_LINK_64 -nolib -Bl link $@.asm
	pause

clean:
	del *.exe
	del *.obj
