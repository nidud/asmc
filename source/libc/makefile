#
# Makefile for LIBC
#

flag = -c -MT -Cs

ifdef avx
flag += -arch:AVX
endif

ifndef nozip
flag += -DSTDZIP
endif
ifdef noutf
flag += -DNOUTF8
endif
# auto link using -MT
ifdef noflt
flag += -DNOSTDFLT
endif

ifdef YACC

ifndef name
name = libasmc
endif

$(name).a:
	asmc64 $(flag) -Zp8 -r *.asm *.s
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ /usr/lib/asmc
	asmc $(flag) -6 -elf -Zp4 -r *.asm *.s
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ /usr/lib/asmc/x86

else

include srcpath

ifndef name
name = libc
endif

flag += -Z7 -I$(inc_dir)

ifdef tty
flag += -D__TTY__
endif
ifdef x86
path = $(lib_dir)\x86
libn = $(lib_dir)\x86\$(name).lib
flag += -6 -coff -Zp4
else
path = $(lib_dir)\x64
libn = $(lib_dir)\x64\$(name).lib
flag += -win64 -frame -Zp8
endif

$(libn):
	asmc $(flag) -r $(src_dir)\libc\*.asm
ifndef tty
	asmc $(flag) -Fo w* -r -ws $(src_dir)\libc\_t*.asm
endif
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
	asmc $(flag) -nologo -MD -Fo msvcrt0 $(src_dir)\libc\crt\_tcrt0.asm
	asmc $(flag) -nologo -MD -Fo msvcrtWin $(src_dir)\libc\crt\_tWinStart.asm
ifndef tty
	asmc $(flag) -nologo -MD -Fo wmsvcrt0 -ws $(src_dir)\libc\crt\_tcrt0.asm
	asmc $(flag) -nologo -MD -Fo wmsvcrtWin -ws $(src_dir)\libc\crt\_tWinStart.asm
endif
	libw -q -b -n -c -fac $(path)\msvcrt0.lib *.obj
	del *.obj


# Test library for the Windows 10 Virtual Terminal

terminal:
#	make tty=1 x86=1
	make tty=1

linux:
	asmc -BlLIBW -6 -mscrt -MT -elf -Zp4 -Cs -r *.asm *.s -link -q -b -n -c $(lib_dir)\x86\libc.a
	asmc -BlLIBW -mscrt -MT -elf64 -Zp8 -Cs -r *.asm *.s -link -q -b -n -c $(lib_dir)\x64\libc.a
	del *.o

regress:
	make -s regress32
	make -s regress64

regress32:
	if exist *.obj del *.obj
	asmc -c -q -coff -Zi -assert -r *.regress
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
	asmc64 -c -q -assert -r *.regress
	for %%f in (*.obj) do call :test_64 %%f
	exit
	:test_64
	linkw op q sys con_64 f %~n1
	if not exist %~n1.exe exit
	%~n1.exe
	if errorlevel 1 exit
	cmd /C del %~n1.obj %~n1.exe

endif
