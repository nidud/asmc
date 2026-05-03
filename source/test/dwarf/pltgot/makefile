
# Note: the order of options affects the link step

all: pltgot clean

pltgot:
	asmc -Zd -Fe pltgot32 -elf -fPIC got.asm -fplt plt.asm
	asmc -Zd -Fe pltgot64 -elf64 -fPIC got.asm -fplt plt.asm

debug32:
	gdb -x ../layout.gdb pltgot32
debug64:
	gdb -x ../layout.gdb pltgot64
clean:
	@rm -f *.o
