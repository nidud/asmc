
test:
	asmc -elf $@.asm
	linkw name $@32. sys elf file $@.o
	asmc -elf64 $@.asm
	linkw name $@64. sys elf64 file $@.o

