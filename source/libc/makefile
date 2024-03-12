#
# Makefile for LIBC
#
ifdef YACC

libasmc.a:
	asmc64 -fpic -Zp8 -D_CRTBLD -Cs -r *.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ /usr/lib/asmc

else

include srcpath

ifdef x86
path = $(lib_dir)\x86
name = $(lib_dir)\x86\libc.lib
flag = -6 -coff -Zp4 -Zi8 -D_CRTBLD -Cs -I$(inc_dir)
else
path = $(lib_dir)\x64
name = $(lib_dir)\x64\libc.lib
flag = -win64 -frame -Zp8 -Zi8 -D_CRTBLD -Cs -I$(inc_dir)
endif
ifdef tty
flag += -D__TTY__
endif
ifdef avx
flag += -arch:AVX
endif

$(name):
	asmc $(flag) -r $(src_dir)\libc\*.asm
	asmc $(flag) -Fo w* -r -ws $(src_dir)\libc\_t*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
	asmc $(flag) -nologo -D_MSVCRT -Fo msvcrt0 $(src_dir)\libc\crt\_tcrt0.asm
	asmc $(flag) -nologo -D_MSVCRT -Fo wmsvcrt0 -ws $(src_dir)\libc\crt\_tcrt0.asm
	asmc $(flag) -nologo -D_MSVCRT -Fo msvcrtWin $(src_dir)\libc\crt\_tWinStart.asm
	asmc $(flag) -nologo -D_MSVCRT -Fo wmsvcrtWin -ws $(src_dir)\libc\crt\_tWinStart.asm
	libw -q -b -n -c -fac $(path)\msvcrt0.lib *.obj
	del *.obj

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
