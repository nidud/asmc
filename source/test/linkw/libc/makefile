
# This assumes libc is build
# and libc for DOS and Linux for Win-targets

libc:
ifdef YACC
	asmc -Flelf_32 -Sf -Sg -Feelf_32 -elf $@.asm
	asmc -Flelf_64 -Sf -Sg -Feelf_64 -elf64 $@.asm
	rm $@.o
else
	asmc -Fldos_t -Sf -Sg -Fedos_t -mt -1 $@.asm
	asmc -Fldos_s -Sf -Sg -Fedos_s -ms -1 $@.asm
	asmc -Fldos_c -Sf -Sg -Fedos_c -mc -1 $@.asm
	asmc -Fldos_m -Sf -Sg -Fedos_m -mm -1 $@.asm
	asmc -Fldos_l -Sf -Sg -Fedos_l -ml -1 $@.asm
	asmc -Flwin_32A -Sf -Sg -Fewin_32A -MT -coff $@.asm
	asmc -Flwin_64A -Sf -Sg -Fewin_64A -MT -win64 -frame $@.asm
	asmc -Flwin_32W -Sf -Sg -Fewin_32W -MT -ws -coff $@.asm
	asmc -Flwin_64W -Sf -Sg -Fewin_64W -MT -ws -win64 -frame $@.asm
	asmc -Flelf_32 -Sf -Sg -Feelf_32. -elf $@.asm -link -nor -d:libc.a
	asmc -Flelf_64 -Sf -Sg -Feelf_64. -elf64 $@.asm -link -nor -d:libc.a
	del $@.o
	del $@.obj
endif
	@pause

clean:
ifdef YACC
	rm elf_32
	rm elf_64
	rm *.lst
else
	del elf_32
	del elf_64
	del *.exe
	del *.lst
endif

vs:
	project -p libc
