
gotx:
	asmc -elf -fPIC -Zd $@.asm
	readelf -r $@.o > reloc.txt
	gdb -x ../layout.gdb ./$@
	@rm -f $@.o
	@rm -f $@
