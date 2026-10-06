ifdef YACC
flags = -elf64
del_obj = rm -f *.o
else
flags = -win64
del_obj = del *.obj
endif

comdat:
	asmc -MT $(flags) -Fefoo foo.asm bar.asm
	asmc -MT $(flags) -Fefoo_gw -Gw foo.asm bar.asm
ifndef YACC
	asmc -MT $(flags) -Bllink -Fefoo_link.exe foo.asm bar.asm
	asmc -MT $(flags) -Bllink -Fefoo_link_gw.exe -Gw foo.asm bar.asm
endif
	dir -l foo*
	pause
	$(del_obj)

