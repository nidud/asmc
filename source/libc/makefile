!include srcpath

all: .libc .libcd .libcw .libcwd

AFLAGS	= /q /coff /Cs /I$(inc_dir) /r
LFLAGS	= /q /b /n /c /fac

.libc:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -D_WIN95 *.asm
	libw $(LFLAGS) $(lib_dir)\libc.lib *.obj
	del *.obj
.libcw:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -ws -D_UNICODE *.asm
	libw $(LFLAGS) $(lib_dir)\libcw.lib *.obj
	del *.obj
.libcd:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -Zi -DDEBUG *.asm
	libw $(LFLAGS) $(lib_dir)\libcd.lib $(src_dir)\libc\*.obj
	del *.obj
.libcwd:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -ws -D_UNICODE -Zi -DDEBUG *.asm
	libw $(LFLAGS) $(lib_dir)\libcwd.lib $(src_dir)\libc\*.obj
	del *.obj
