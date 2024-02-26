#
# Makefile for [A]LIBC
#
ifdef YACC

alibc.a:
	asmc64 -Zp8 -D_CRTBLD -Cs -r *.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp alibc.a /lib

else

include srcpath

path = $(lib_dir)\x64
ifdef x86
path = $(lib_dir)\x86
endif
name = libc.lib
type = obj
lcfg = -fac
flag = -win64 -frame -Zp8 -Zi8
ifdef tty
flag += -D__TTY__
endif
ifdef avx
flag += -arch:AVX
endif
ifdef linux
name = libc.a
type = o
flag = -elf64 -Zp8
lcfg = -fag
else
ifdef x86
flag = -6 -coff -Zp4 -Zi8
endif
endif

$(path)\$(name):
	asmc $(flag) -D_CRTBLD -Cs -I$(inc_dir) -r $(src_dir)\libc\*.asm
	asmc $(flag) -D_CRTBLD -Cs -I$(inc_dir) -Fo w* -r -ws $(src_dir)\libc\_t*.asm
	libw -q -b -n -c $(lcfg) $@ *.$(type)
	del *.$(type)

linux:
	make linux=1

win32:
	make x86=1

winavx:
	make avx=1

regress:
	make -s regress32
	make -s regress64

regress32:
	if exist *.obj del *.obj
	asmc -q -coff -Zi -assert -r *.regress
	for %%f in (*.obj) do call :test_32 %%f
	exit
	:test_32
	linkw sys con_32 file %~n1.obj
	if not exist %~n1.exe exit
	%~n1.exe
	if errorlevel 1 exit
	cmd /C del %~n1.obj %~n1.exe

regress64:
	if exist *.obj del *.obj
	asmc64 -q -assert -r *.regress
	for %%f in (*.obj) do call :test_64 %%f
	exit
	:test_64
	linkw op q sys con_64 f %~n1
	if not exist %~n1.exe exit
	%~n1.exe
	if errorlevel 1 exit
	cmd /C del %~n1.obj %~n1.exe
endif
