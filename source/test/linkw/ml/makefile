ifndef CC
CC = ml
endif

all: test clean

test:
	$(CC) -Bl linkw.exe $@.asm
	$@
asmc:
	make CC=asmc
clean:
	del *.obj
	del *.exe
	del *.lnk
