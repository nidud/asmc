ifndef CC
CC = ml64
endif

all: test clean

test:
	$(CC) -Bl linkw.exe $@.asm
	$@
asmc:
	make CC=asmc64
clean:
	del *.obj
	del *.exe
	del *.lnk
