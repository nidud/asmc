#
# Visual C version 6 used for debug
# Open Watcom used to add the DZ.ICO file
#
debug = 0

msvc = \vc
watc = \watcom

asmc = %AsmcDir%
path = $(asmc)\source\tools\dz

#
# use full path of this directory (source level debug)
#
include = -I$(path)\include -I$(asmc)\include

CC  = $(asmc)\bin\asmc /coff /Cs /Zi /Gz /D__BMP__ $(include)
RC  = $(asmc)\bin\iddc /coff
LIB = $(asmc)\bin\libw /q /b /n /c /fac

!if $(debug)
LINK = $(msvc)\bin\link /map /debug /subsystem:console /libpath:$(asmc)\lib
!else
LINK = $(asmc)\bin\linkw op stub=$(path)\res\dz.bin file
ICON = $(watc)\binnt\wrc -q $(path)\res\dz.res $@
!endif

# Recompile LIBC as STDCALL

libc_path = $(asmc)\source

libc_objecs = \
    lib32\conio\_gotoxy.obj \
    lib32\conio\_wherex.obj \
    lib32\crtl\__allocwpath.obj \
    lib32\crtl\__coreleft.obj \
    lib32\crtl\__crtCorExitProcess.obj \
    lib32\crtl\__crtExitProcess.obj \
    lib32\crtl\__FTToTime.obj \
    lib32\crtl\__isexec.obj \
    lib32\crtl\__STToTime.obj \
    lib32\crtl\__xtol.obj \
    lib32\crtl\__xtoi64.obj \
    lib32\crtl\_exitflag.obj \
    lib32\crtl\_initterm.obj \
    lib32\crtl\crt0init.obj \
    lib32\crtl\memxchg.obj \
    lib32\crtl\sselevel.obj \
    lib32\crtl\strext.obj \
    lib32\crtl\strfcat.obj \
    lib32\crtl\strfn.obj \
    lib32\direct\_chdir.obj \
    lib32\direct\_chdrive.obj \
    lib32\direct\_getcwd.obj \
    lib32\direct\_getdcwd.obj \
    lib32\direct\_getdrive.obj \
    lib32\direct\_rmdir.obj \
    lib32\errno\_sys_errlist.obj \
    lib32\errno\errno.obj \
    lib32\errno\osmaperr.obj \
    lib32\io\_access.obj \
    lib32\io\_close.obj \
    lib32\io\_filelength.obj \
    lib32\io\_ioinit.obj \
    lib32\io\_isatty.obj \
    lib32\io\_lseek.obj \
    lib32\io\_lseeki64.obj \
    lib32\io\_osopenA.obj \
    lib32\io\_write.obj \
    lib32\io\getosfhnd.obj \
    lib32\io\osread.obj \
    lib32\io\oswrite.obj \
    lib32\ltype\_ltype.obj \
    lib32\malloc\_aligned_malloc.obj \
    lib32\malloc\_amblksiz.obj \
    lib32\malloc\alloc.obj \
    lib32\malloc\alloca.obj \
    lib32\stdio\__lookuptable.obj \
    lib32\stdio\__nullstring.obj \
    lib32\stdio\_bufin.obj \
    lib32\stdio\_file.obj \
    lib32\stdio\_flsbuf.obj \
    lib32\stdio\_freebuf.obj \
    lib32\stdio\_getbuf.obj \
    lib32\stdio\_output.obj \
    lib32\stdio\_print.obj \
    lib32\stdio\fclose.obj \
    lib32\stdio\fflush.obj \
    lib32\stdio\fputc.obj \
    lib32\stdio\ftobufin.obj \
    lib32\stdio\sprintf.obj \
    lib32\stdlib\__argc.obj \
    lib32\stdlib\__argv.obj \
    lib32\stdlib\__setenvp.obj \
    lib32\stdlib\_atoi64.obj \
    lib32\stdlib\_environ.obj \
    lib32\stdlib\_pgmpath.obj \
    lib32\stdlib\atol.obj \
    lib32\stdlib\doexit.obj \
    lib32\stdlib\exit.obj \
    lib32\stdlib\setargv.obj \
    lib32\string\_strdup.obj \
    lib32\string\_stricmp.obj \
    lib32\string\_strnicmp.obj \
    lib32\string\_strrev.obj \
    lib32\string\memcmp.obj \
    lib32\string\memcpy.obj \
    lib32\string\memset.obj \
    lib32\string\strcat.obj \
    lib32\string\strchr.obj \
    lib32\string\strcmp.obj \
    lib32\string\strcpy.obj \
    lib32\string\strlen.obj \
    lib32\string\strncmp.obj \
    lib32\string\strncpy.obj \
    lib32\string\strrchr.obj \
    lib32\string\strstr.obj \
    lib32\time\__TimeToFT.obj \
    lib32\time\__TimeToST.obj \
    lib32\time\_days.obj \
    lib32\time\_loctotime_t.obj \
    lib32\time\_time.obj \
    lib32\time\_tzset.obj \
    lib32\time\atodate.obj \
    lib32\time\atotime.obj \
    lib32\time\clock.obj \
    lib32\time\DaysInFebruary.obj \
    lib32\time\DaysInMonth.obj \
    lib32\time\fdatetostr.obj \
    lib32\time\ftimetostr.obj \
    lib32\time\GetDayCount.obj \
    lib32\time\GetWeekDay.obj \
    lib32\time\SystemDateToString.obj \
    lib32\time\SystemTimeToString.obj \
    lib32\time\TDateToString.obj \
    lib32\time\timeset.obj \
    lib32\winbase\GetConsoleWindow.obj \
    lib32\winbase\GetFileSizeEx.obj \
    lib32\winbase\kernel32.obj \
    lib32\winbase\SetFilePointerEx.obj \
    lib32\winuser\GetForegroundWindow.obj \
    lib32\winuser\GetKeyState.obj \
    lib32\winuser\SetWindowPos.obj \
    lib32\winuser\user32.obj

all: libc.lib dz.exe clean

{$(libc_path)}.asm.obj:
    $(CC) -nologo $<

libc.lib: $(libc_objecs)
    $(RC) /r $(path)\res\*.idd
    $(CC) /r $(path)\source\*.asm
    $(LIB) $@ *.obj
    @del *.obj

dz.exe:
    $(CC) -nologo $(path)\dz.asm
    $(LINK) dz.obj
    $(ICON)

clean:
    @del libc.lib
    @del dz.obj

