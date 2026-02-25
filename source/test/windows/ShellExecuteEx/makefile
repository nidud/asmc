
all: ShellExecuteEx clean

ShellExecuteEx:
	asmc64 -pe -ws $@.asm
	$@
	@pause

clean:
	del ShellExecuteEx.exe
	del ShellExecuteEx.obj

vs:
	project -p -u ShellExecuteEx
