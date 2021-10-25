ifndef __STDIO_INC
define __STDIO_INC
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

FILENAME_MAX	equ 260

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

EOF		equ (-1)

ifndef _FILE_DEFINED
define _FILE_DEFINED
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
LPFILE		typedef ptr _iobuf
endif

_fileno proto fastcall fp:LPFILE {
    mov eax,[fp].FILE._file
    }

if not defined(_MSVCRT) or defined(_CRTBLD)
ifndef _LINUX
externdef	_bufin:BYTE
externdef	_iob:_iobuf
externdef	stdout:_iobuf
externdef	stderr:_iobuf
externdef	_osfhnd:HANDLE
externdef	hStdInput:HANDLE
externdef	hStdOutput:HANDLE
externdef	hStdError:HANDLE
endif
elseifdef _LIBCMT
_iob		equ <[__acrt_iob_func(0)]>
stdout		equ <[__acrt_iob_func(1)]>
stderr		equ <[__acrt_iob_func(2)]>
else
_iob		equ <[__iob_func()]>
stdout		equ <[__iob_func()+sizeof(_iobuf)]>
stderr		equ <[__iob_func()+sizeof(_iobuf)*2]>
endif
stdin		equ <_iob>

_output		proto __cdecl :LPFILE, :LPSTR, :PVOID
sprintf		proto _CDecl :LPSTR, :LPSTR, :VARARG
ftobufin	proto _CDecl :LPSTR, :VARARG
printf		proto _CDecl :LPSTR, :VARARG
fprintf		proto _CDecl :LPFILE, :LPSTR, :VARARG
scanf		proto _CDecl :LPSTR, :VARARG
puts		proto __cdecl :LPSTR
getc		proto __cdecl :LPSTR
fopen		proto __cdecl :LPSTR, :LPSTR
fopen_s		proto __cdecl :ptr ptr FILE, :LPSTR, :LPSTR
fclose		proto __cdecl :LPFILE
fgetc		proto __cdecl :LPFILE
vsprintf	proto __cdecl :LPSTR, :LPSTR, :PVOID
_vsnprintf	proto __cdecl :LPSTR, :size_t, :LPSTR, :PVOID
vfprintf	proto __cdecl :LPFILE,:LPSTR, :PVOID
fread		proto __cdecl :LPSTR, :SINT, :SINT, :LPFILE
fwrite		proto __cdecl :LPSTR, :SINT, :SINT, :LPFILE
fseek		proto __cdecl :LPFILE,:SIZE_T, :SIZE_T
fgets		proto __cdecl :LPSTR, :SINT, :LPFILE
fputs		proto __cdecl :LPSTR, :LPFILE
_fputchar	proto __cdecl :SINT
fputc		proto __cdecl :SINT, :LPFILE
feof		proto __cdecl :LPFILE
ftell		proto __cdecl :LPFILE
perror		proto __cdecl :LPSTR
fflush		proto __cdecl :LPFILE
rewind		proto __cdecl :LPFILE
_flsbuf		proto __cdecl :SINT, :LPFILE
_flushall	proto __cdecl
_freebuf	proto __cdecl :LPFILE
_filbuf		proto __cdecl :LPFILE
_getst		proto __cdecl
_ftbuf		proto __cdecl :SINT, :LPFILE
_stbuf		proto __cdecl :LPFILE
_getbuf		proto __cdecl :LPFILE
setvbuf		proto __cdecl :LPFILE, :LPSTR, :SIZE_T, :SIZE_T
setbuf		proto __cdecl :LPFILE, :LPSTR
ungetc		proto __cdecl :SINT, :LPFILE
_openfile	proto __cdecl :LPSTR, :LPSTR, :SINT, :LPFILE
ifdef _MSVCRT
__getmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__wgetmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__iob_func	proto __cdecl
__acrt_iob_func proto __cdecl :dword
endif

ifndef _WSTDIO_DEFINED
define _WSTDIO_DEFINED

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t		typedef WORD
endif

ifndef _WCTYPE_T_DEFINED
define _WCTYPE_T_DEFINED
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
swprintf_s	proto _CDecl :ptr wchar_t, :size_t, :ptr wchar_t, :VARARG
vfwprintf	proto __cdecl :ptr FILE, :ptr wchar_t, :PVOID
vwprintf	proto __cdecl :ptr wchar_t, :PVOID
_vsnwprintf	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :PVOID
vswprintf	proto __cdecl :ptr wchar_t, :ptr wchar_t, :PVOID
fwscanf		proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
swscanf		proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
swscanf_s	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
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

.pragma list(pop)
endif
