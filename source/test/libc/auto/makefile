# Makefile for auto link

flags = -MT
ifdef YACC
fl32 = -elf -fno-pic
else
fl32 = -coff
endif

all: auto clean

auto:
	asmc $(flags) $(fl32) -Fo $@320 $@.asm
	asmc $(flags) $(fl32) -DUSEFLT -Fo $@322 $@.asm
	asmc64 $(flags) -Fo $@640 $@.asm
	asmc64 $(flags) -DUSEFLT -Fo $@642 $@.asm
ifndef YACC
	asmc $(flags) $(fl32) -DUSEARGV -Fo $@321 $@.asm
	asmc $(flags) $(fl32) -DUSEFLT -DUSEARGV -Fo $@323 $@.asm
	asmc64 $(flags) -DUSEARGV -Fo $@641 $@.asm
	asmc64 $(flags) -DUSEFLT -DUSEARGV -Fo $@643 $@.asm
endif

clean:
ifdef YACC
	rm *.o
else
	del *.obj
endif

vs:
	project -p auto
