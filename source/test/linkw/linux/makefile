
test:
	asmc -c -elf $@.asm
	linkw name $@32. sys elf file $@.o
	asmc -c -elf64 $@.asm
	linkw name $@64. sys elf64 file $@.o

