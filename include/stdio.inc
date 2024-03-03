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
_iobuf		struct size_t
_ptr		LPTSTR ?
_cnt		int_t ?
_base		string_t ?
_flag		int_t ?
_file		int_t ?
if defined(_WIN64) or not defined(__UNIX__)
_charbuf	int_t ?
endif
_bufsiz		int_t ?
if defined(__UNIX__) and not defined(_WIN64)
_ungotten	dw ?
else
_tmpfname	LPTSTR ?
endif
_iobuf		ends
FILE		typedef _iobuf
LPFILE		typedef ptr _iobuf
endif

if not defined(_MSVCRT) or defined(_CRTBLD)
externdef	_iob:_iobuf
externdef	_bufin:BYTE
externdef	stdin:ptr _iobuf
externdef	stdout:ptr _iobuf
externdef	stderr:ptr _iobuf
elseifdef _LIBCMT
stdin		equ <__acrt_iob_func(0)>
stdout		equ <&[__acrt_iob_func(1)]>
stderr		equ <&[__acrt_iob_func(2)]>
else
stdin		equ <__iob_func()>
stdout		equ <&[__iob_func()+sizeof(_iobuf)]>
stderr		equ <&[__iob_func()+sizeof(_iobuf)*2]>
endif

ifdef __UNIX__
_fileno		equ <fileno>
endif
_fileno		proto __cdecl :LPFILE

_output		proto __cdecl :LPFILE, :string_t, :ptr
sprintf		proto __Cdecl :string_t, :string_t, :vararg
_scprintf	proto __Cdecl :string_t, :vararg
ftobufin	proto __Cdecl :string_t, :ptr
printf		proto __Cdecl :string_t, :vararg
fprintf		proto __Cdecl :LPFILE, :string_t, :vararg
scanf		proto __Cdecl :string_t, :vararg
puts		proto __cdecl :string_t
getc		proto __cdecl :LPFILE
fopen		proto __cdecl :string_t, :string_t
fopen_s		proto __cdecl :ptr LPFILE, :string_t, :string_t
fclose		proto __cdecl :LPFILE
fgetc		proto __cdecl :LPFILE
getchar		proto __cdecl
vsprintf	proto __cdecl :string_t, :string_t, :ptr
_vsnprintf	proto __cdecl :string_t, :size_t, :string_t, :ptr
_vscprintf	proto __cdecl :string_t, :ptr
vfprintf	proto __cdecl :LPFILE,:string_t, :ptr
fread		proto __cdecl :string_t, :int_t, :int_t, :LPFILE
fwrite		proto __cdecl :string_t, :int_t, :int_t, :LPFILE
fseek		proto __cdecl :LPFILE,:SIZE_T, :SIZE_T
fgets		proto __cdecl :string_t, :int_t, :LPFILE
fputs		proto __cdecl :string_t, :LPFILE
_fputchar	proto __cdecl :int_t
fputc		proto __cdecl :int_t, :LPFILE
feof		proto __cdecl :LPFILE
ftell		proto __cdecl :LPFILE
perror		proto __cdecl :string_t
fflush		proto __cdecl :LPFILE
rewind		proto __cdecl :LPFILE
_flsbuf		proto __cdecl :int_t, :LPFILE
_flushall	proto __cdecl
_freebuf	proto __cdecl :LPFILE
_filbuf		proto __cdecl :LPFILE
_getst		proto __cdecl
_ftbuf		proto __cdecl :int_t, :LPFILE
_stbuf		proto __cdecl :LPFILE
_getbuf		proto __cdecl :LPFILE
setvbuf		proto __cdecl :LPFILE, :string_t, :int_t, :size_t
setbuf		proto __cdecl :LPFILE, :string_t
ungetc		proto __cdecl :int_t, :LPFILE
_openfile	proto __cdecl :string_t, :string_t, :int_t, :LPFILE

__iob_func	proto __cdecl
__acrt_iob_func proto __cdecl :dword

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
_wfsopenproto	proto __cdecl :wstring_t, :wstring_t
else
_wfsopenproto	proto __cdecl :wstring_t, :wstring_t, :int_t
endif

fgetwc		proto __cdecl :LPFILE
_fgetwchar	proto __cdecl
fputwc		proto __cdecl :int_t, :LPFILE
_fputwchar	proto __cdecl :wint_t
getwc		proto __cdecl :LPFILE
getwchar	proto __cdecl
putwc		proto __cdecl :wint_t, :LPFILE
putwchar	proto __cdecl :wint_t
ungetwc		proto __cdecl :int_t, :LPFILE
fgetws		proto __cdecl :wstring_t, :int_t, :LPFILE
fputws		proto __cdecl :wstring_t, :LPFILE
_getws		proto __cdecl :wstring_t
_putws		proto __cdecl :wstring_t
fwprintf	proto __Cdecl :LPFILE, :wstring_t, :vararg
wprintf		proto __Cdecl :wstring_t, :vararg
_snwprintf	proto __Cdecl :wstring_t, :size_t, :wstring_t, :vararg
swprintf	proto __Cdecl :wstring_t, :wstring_t, :vararg
_scwprintf	proto __Cdecl :wstring_t, :vararg
swprintf_s	proto __Cdecl :wstring_t, :size_t, :wstring_t, :vararg
vfwprintf	proto __cdecl :LPFILE, :wstring_t, :ptr
vwprintf	proto __cdecl :wstring_t, :ptr
_vsnwprintf	proto __cdecl :wstring_t, :size_t, :wstring_t, :ptr
_vscwprintf	proto __cdecl :wstring_t, :ptr
vswprintf	proto __cdecl :wstring_t, :wstring_t, :ptr
fwscanf		proto __Cdecl :LPFILE, :wstring_t, :vararg
swscanf		proto __Cdecl :wstring_t, :wstring_t, :vararg
swscanf_s	proto __Cdecl :wstring_t, :wstring_t, :vararg
wscanf		proto __Cdecl :wstring_t, :vararg
_wfdopen	proto __cdecl :int_t, :wstring_t
_wfopen		proto __cdecl :wstring_t, :wstring_t
_wfreopen	proto __cdecl :wstring_t, :wstring_t, :LPFILE
_wperror	proto __cdecl :wstring_t
_wpopen		proto __cdecl :wstring_t, :wstring_t
_wremove	proto __cdecl :wstring_t
_wtempnam	proto __cdecl :wstring_t, :wstring_t
_wtmpnam	proto __cdecl :wstring_t

_flswbuf	proto __cdecl :int_t, :LPFILE
_filwbuf	proto __cdecl :LPFILE
_woutput	proto __cdecl :LPFILE, :wstring_t, :ptr
_wopenfile	proto __cdecl :wstring_t, :wstring_t, :int_t, :LPFILE

endif ; _WSTDIO_DEFINED

ifdef _UNICODE
define _toutput		<_woutput>
define _tfilbuf		<_filwbuf>
define _tflsbuf		<_flswbuf>
define _topenfile	<_wopenfile>
else
define _toutput		<_output>
define _tfilbuf		<_filbuf>
define _tflsbuf		<_flsbuf>
define _topenfile	<_openfile>
endif

.pragma list(pop)
endif
