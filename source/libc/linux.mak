!include srcpath

flags = -D_CRTBLD -Cs -I$(inc_dir)

alibc.a:
	asmc $(flags) -elf64 -Zp8 -r *.asm
	libw -q -b -n -c -fag $@ *.o
	del *.o

