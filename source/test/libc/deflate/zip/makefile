
all: zip clean

zip:
	asmc64 -q $@.asm
ifdef YACC
	./$@ -r include.zip "../../../../../include/*.inc"
else
	$@ -r include.zip ../../../../../include/*.inc
endif
	@pause

clean:
ifdef YACC
	rm ./zip.o
	rm ./zip
else
	del zip.exe
	del zip.obj
endif

vs:
	project -p zip
