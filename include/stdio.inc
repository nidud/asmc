ifndef __STDIO_INC
__STDIO_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifdef __PE__
option	dllimport:<msvcrt>
endif

SEEK_CUR	equ 1
SEEK_END	equ 2
SEEK_SET	equ 0

_NSTREAM_	equ 20
_MAXIOBUF	equ 0x4000
_INTIOBUF	equ 0x1000
_MINIOBUF	equ 0x0200

_IOFBF		equ 0x0000
_IOREAD		equ 0x0001
_IOWRT		equ 0x0002
_IONBF		equ 0x0004
_IOMYBUF	equ 0x0008
_IOEOF		equ 0x0010
_IOERR		equ 0x0020
_IOSTRG		equ 0x0040
_IOLBF		equ 0x0040
_IORW		equ 0x0080
_IOYOURBUF	equ 0x0100
_IOSETVBUF	equ 0x0400
_IOFEOF		equ 0x0800
_IOFLRTN	equ 0x1000
_IOCTRLZ	equ 0x2000
_IOCOMMIT	equ 0x4000

ifndef _FILE_DEFINED
_FILE_DEFINED equ <>
_iobuf		STRUC SIZE_T
_ptr		LPSTR ?
_cnt		SINT ?
_base		LPSTR ?
_flag		SINT ?
_file		SINT ?
_charbuf	SINT ?
_bufsiz		SINT ?
_tmpfname	LPSTR ?
_iobuf		ENDS
FILE		typedef _iobuf
LPFILE		TYPEDEF PTR _iobuf
endif

ifndef __PE__
externdef	_bufin:BYTE
externdef	_iob:_iobuf
externdef	stdout:_iobuf
externdef	stderr:_iobuf
externdef	_osfhnd:HANDLE
externdef	hStdInput:HANDLE
externdef	hStdOutput:HANDLE
externdef	hStdError:HANDLE
endif

_output		proto __cdecl :LPFILE, :LPSTR, :PVOID
_print		proto _CDecl :LPSTR, :VARARG
sprintf		proto _CDecl :LPSTR, :LPSTR, :VARARG
ftobufin	proto _CDecl :LPSTR, :VARARG
printf		proto _CDecl :LPSTR, :VARARG
fprintf		proto _CDecl :LPFILE, :LPSTR, :VARARG
puts		proto __cdecl :LPSTR
fopen		proto __cdecl :LPSTR, :LPSTR
fclose		proto __cdecl :LPFILE
fgetc		proto __cdecl :LPFILE
vsprintf	proto __cdecl :LPSTR, :LPSTR, :PVOID
vfprintf	proto __cdecl :LPFILE,:LPSTR, :PVOID
fread		proto __cdecl :LPSTR, :SINT, :SINT, :LPFILE
fwrite		proto __cdecl :LPSTR, :SINT, :SINT, :LPFILE
fseek		proto __cdecl :LPFILE,:SIZE_T, :SIZE_T
fgets		proto __cdecl :LPSTR, :SINT, :LPFILE
fputs		proto __cdecl :LPSTR, :LPFILE
fputc		proto __cdecl :SINT, :LPFILE
feof		proto __cdecl :LPFILE
ftell		proto __cdecl :LPFILE
perror		proto __cdecl :LPSTR
fflush		proto __cdecl :LPFILE
rewind		proto __cdecl :LPFILE
_flsbuf		proto __cdecl :SIZE_T, :LPFILE
_flushall	proto __cdecl
_freebuf	proto __cdecl :LPFILE
_filbuf		proto __cdecl :LPFILE
_getst		proto __cdecl
_ftbuf		proto __cdecl :ULONG, :LPFILE
_stbuf		proto __cdecl :LPFILE
_getbuf		proto __cdecl :LPFILE
setvbuf		proto __cdecl :LPFILE, :LPSTR, :SIZE_T, :SIZE_T
setbuf		proto __cdecl :LPFILE, :LPSTR
ungetc		proto __cdecl :SINT, :LPFILE

ifndef _WSTDIO_DEFINED
_WSTDIO_DEFINED equ <>

ifndef _WCHAR_T_DEFINED
_WCHAR_T_DEFINED equ <>
wchar_t		typedef WORD
endif

ifndef _WCTYPE_T_DEFINED
_WCTYPE_T_DEFINED equ <>
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
endif

ifdef  _POSIX_
_wfsopenproto	proto __cdecl :ptr wchar_t, :ptr wchar_t
else
_wfsopenproto	proto __cdecl :ptr wchar_t, :ptr wchar_t, :SINT
endif

fgetwc		proto __cdecl :ptr FILE
_fgetwchar	proto __cdecl
fputwc		proto __cdecl :wint_t, :ptr FILE
_fputwchar	proto __cdecl :wint_t
getwc		proto __cdecl :ptr FILE
getwchar	proto __cdecl
putwc		proto __cdecl :wint_t, :ptr FILE
putwchar	proto __cdecl :wint_t
ungetwc		proto __cdecl :wint_t, :ptr FILE
fgetws		proto __cdecl :ptr wchar_t, :SINT, :ptr FILE
fputws		proto __cdecl :ptr wchar_t, :ptr FILE
_getws		proto __cdecl :ptr wchar_t
_putws		proto __cdecl :ptr wchar_t
fwprintf	proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
wprintf		proto _CDecl :ptr wchar_t, :VARARG
_snwprintf	proto _CDecl :ptr wchar_t, :size_t, :ptr wchar_t, :VARARG
swprintf	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
vfwprintf	proto __cdecl :ptr FILE, :ptr wchar_t, :PVOID
vwprintf	proto __cdecl :ptr wchar_t, :PVOID
_vsnwprintf	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :PVOID
vswprintf	proto __cdecl :ptr wchar_t, :ptr wchar_t, :PVOID
fwscanf		proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
swscanf		proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
wscanf		proto _CDecl :ptr wchar_t, :VARARG

_wfdopen	proto __cdecl :SINT, :ptr wchar_t
_wfopen		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wfreopen	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr FILE
_wperror	proto __cdecl :ptr wchar_t
_wpopen		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wremove	proto __cdecl :ptr wchar_t
_wtempnam	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wtmpnam	proto __cdecl :ptr wchar_t

_flswbuf	proto __cdecl :SINT, :LPFILE
_filwbuf	proto __cdecl :LPFILE
_woutput	proto __cdecl :LPFILE, :LPWSTR, :PVOID

endif ; _WSTDIO_DEFINED

.list
endif ; __STDIO_INC
