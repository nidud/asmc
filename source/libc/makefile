#
# Makefile for LIBC
#

flag = -c -MT -Cs

ifdef avx
flag += -arch:AVX
endif

ifdef zip
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
	asmc64 $(flag) -Zd -Zp8 -r *.asm *.s
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ /usr/lib/asmc
	asmc $(flag) -6 -elf -Zd -Zp4 -r *.asm *.s
	ar rcs $@ *.o
	rm *.o
	sudo cp $@ /usr/lib/asmc/x86

else

include srcpath

ifndef name
name = libc
endif

flag += -Zi -I$(inc_dir)

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
	asmc $(flag) -Fo $(path)\noarg $(lib_dir)\noarg.asm
	asmc $(flag) -Fo $(path)\noflt $(lib_dir)\noflt.asm
	asmc $(flag) -r $(src_dir)\libc\*.asm
ifndef tty
	asmc $(flag) -Fo w* -r -ws $(src_dir)\libc\_t*.asm
endif
	libw -q -b -n -c -fac $@ *.obj
	del *.obj
	asmc $(flag) -nologo -MD $(src_dir)\libc\crt\_tcrt0.asm $(src_dir)\libc\crt\_tWinStart.asm
ifndef tty
	asmc $(flag) -nologo -MD -Fo wcrt0 -ws $(src_dir)\libc\crt\_tcrt0.asm
	asmc $(flag) -nologo -MD -Fo wWinStart -ws $(src_dir)\libc\crt\_tWinStart.asm
endif
	libw -q -b -n -c -fac $(path)\msvcrt0.lib *.obj
	del *.obj

# Test library for the Windows 10 Virtual Terminal

terminal:
#	make tty=1 x86=1
	make tty=1

linux:
	asmc -c -q -mscrt -elf -Fo $(lib_dir)\x86\noflt $(lib_dir)\noflt.asm
	asmc -c -q -mscrt -elf64 -Fo $(lib_dir)\x64\noflt $(lib_dir)\noflt.asm
	asmc -BlLIBW -6 -mscrt -MT -elf -Zp4 -Cs -r $(src_dir)\libc\*.asm $(src_dir)\libc\*.s -link -q -b -n -c $(lib_dir)\x86\libc.a
	asmc -BlLIBW -mscrt -MT -elf64 -Zp8 -Cs -r $(src_dir)\libc\*.asm $(src_dir)\libc\*.s -link -q -b -n -c $(lib_dir)\x64\libc.a
	del *.o

regress:
	if exist *.obj del *.obj
	asmc -c -q -coff -assert -r $(src_dir)\libc\*.regress
	for %%f in (*.obj) do call :test %%f
	asmc -c -win64 -q -assert -r $(src_dir)\libc\*.regress
	for %%f in (*.obj) do call :test %%f
	echo Everything is okay
	exit
	:test
	linkw op q file %~n1.obj
	if not exist %~n1.exe exit
	%~n1.exe
	if errorlevel 1 exit
	cmd /C del %~n1.obj %~n1.exe

endif
