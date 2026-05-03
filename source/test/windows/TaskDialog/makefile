# Makefile for TaskDialog
# Thu Apr 10 2025

flags = -peg -ws

TaskDialog:
	asmc64 $(flags) $@.asm
	$@
	@pause

clean:
	del TaskDialog.exe
	del TaskDialog.obj

vs:
	project -p -w -u TaskDialog
