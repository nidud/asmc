!include srcpath

all: .libc .libcd .libcw .libcwd

AFLAGS	= /coff /Cs /I$(inc_dir) /r
LFLAGS	= /b /n /c /fac

.libc:
	iddc -coff -r *.idd
	asmc $(AFLAGS) *.asm
	libw $(LFLAGS) $(lib_dir)\libc.lib *.obj
	del *.obj

.libcw:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -ws -D_UNICODE *.asm
	libw $(LFLAGS) $(lib_dir)\libcw.lib *.obj
	del *.obj

.libcd:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -Zi -DDEBUG $(src_dir)\libc\*.asm
	libw $(LFLAGS) $(lib_dir)\libcd.lib $(src_dir)\libc\*.obj
	del *.obj

.libcwd:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -ws -D_UNICODE -Zi -DDEBUG $(src_dir)\libc\*.asm
	libw $(LFLAGS) $(lib_dir)\libcwd.lib $(src_dir)\libc\*.obj
	del *.obj

.libc95:
	iddc -coff -r *.idd
	asmc $(AFLAGS) -D_WIN95 *.asm
	libw $(LFLAGS) $(lib_dir)\libc95.lib *.obj
	del *.obj
