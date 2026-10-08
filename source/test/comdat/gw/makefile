ifdef YACC
flags = -elf64
delobj = rm -f *.o
binary = ./comdat
else
flags = -win64
delobj = del *.obj
binary = comdat
endif

comdat:
	asmc -MT -Gw $(flags) -Fe$@ foo.asm bar.asm
	$(binary)
	pause
	$(delobj)

