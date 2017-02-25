ifndef __LIBC_INC
 include libc.inc
endif
.xlist
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

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
_FILE_DEFINED	equ 1
endif
LPFILE		TYPEDEF PTR _iobuf

externdef	_bufin:BYTE
externdef	_iob:_iobuf
externdef	stdout:_iobuf
externdef	stderr:_iobuf
externdef	_osfhnd:HANDLE
externdef	hStdInput:HANDLE
externdef	hStdOutput:HANDLE
externdef	hStdError:HANDLE

_output		PROTO :LPFILE, :LPSTR, :PVOID
_print		PROTO _CDecl :LPSTR, :VARARG
sprintf		PROTO _CDecl :LPSTR, :LPSTR, :VARARG
ftobufin	PROTO _CDecl :LPSTR, :VARARG
printf		PROTO _CDecl :LPSTR, :VARARG
fprintf		PROTO _CDecl :LPFILE, :LPSTR, :VARARG
puts		PROTO :LPSTR
fopen		PROTO :LPSTR, :LPSTR
fclose		PROTO :LPFILE
fgetc		PROTO :LPFILE
vsprintf	PROTO :LPSTR, :LPSTR, :PVOID
vfprintf	PROTO :LPFILE,:LPSTR, :PVOID
fread		PROTO :LPSTR, :SINT, :SINT, :LPFILE
fwrite		PROTO :LPSTR, :SINT, :SINT, :LPFILE
fseek		PROTO :LPFILE,:SIZE_T, :SIZE_T
fgets		PROTO :LPSTR, :SINT, :LPFILE
fputs		PROTO :LPSTR, :LPFILE
fputc		PROTO :SINT, :LPFILE
feof		PROTO :LPFILE
ftell		PROTO :LPFILE
perror		PROTO :LPSTR
fflush		PROTO :LPFILE
rewind		PROTO :LPFILE
_flsbuf		PROTO :SIZE_T, :LPFILE
_freebuf	PROTO :LPFILE
_filbuf		PROTO :LPFILE
_getst		PROTO
_ftbuf		PROTO :ULONG, :LPFILE
_stbuf		PROTO :LPFILE
_getbuf		PROTO :LPFILE
setvbuf		PROTO :LPFILE, :LPSTR, :SIZE_T, :SIZE_T
setbuf		PROTO :LPFILE, :LPSTR
ungetc		PROTO :SINT, :LPFILE

ifndef _WSTDIO_DEFINED
ifndef _WCHAR_T_DEFINED
wchar_t			typedef WORD
_WCHAR_T_DEFINED	equ 1
endif
ifndef _WCTYPE_T_DEFINED
wint_t			typedef wchar_t
wctype_t		typedef wchar_t
_WCTYPE_T_DEFINED	equ 1
endif
ifdef  _POSIX_
_wfsopenproto	proto :ptr wchar_t, :ptr wchar_t
else
_wfsopenproto	proto :ptr wchar_t, :ptr wchar_t, :SINT
endif

fgetwc		proto :ptr FILE
_fgetwchar	proto
fputwc		proto :wint_t, :ptr FILE
_fputwchar	proto :wint_t
getwc		proto :ptr FILE
getwchar	proto
putwc		proto :wint_t, :ptr FILE
putwchar	proto :wint_t
ungetwc		proto :wint_t, :ptr FILE
fgetws		proto :ptr wchar_t, :SINT, :ptr FILE
fputws		proto :ptr wchar_t, :ptr FILE
_getws		proto :ptr wchar_t
_putws		proto :ptr wchar_t
fwprintf	proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
wprintf		proto _CDecl :ptr wchar_t, :VARARG
_snwprintf	proto _CDecl :ptr wchar_t, :size_t, :ptr wchar_t, :VARARG
swprintf	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
vfwprintf	proto :ptr FILE, :ptr wchar_t, :PVOID
vwprintf	proto :ptr wchar_t, :PVOID
_vsnwprintf	proto :ptr wchar_t, :size_t, :ptr wchar_t, :PVOID
vswprintf	proto :ptr wchar_t, :ptr wchar_t, :PVOID
fwscanf		proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
swscanf		proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
wscanf		proto _CDecl :ptr wchar_t, :VARARG

_wfdopen	proto :SINT, :ptr wchar_t
_wfopen		proto :ptr wchar_t, :ptr wchar_t
_wfreopen	proto :ptr wchar_t, :ptr wchar_t, :ptr FILE
_wperror	proto :ptr wchar_t
_wpopen		proto :ptr wchar_t, :ptr wchar_t
_wremove	proto :ptr wchar_t
_wtempnam	proto :ptr wchar_t, :ptr wchar_t
_wtmpnam	proto :ptr wchar_t

_flswbuf	proto :SINT, :LPFILE
_filwbuf	proto :LPFILE
_woutput	proto :LPFILE, :LPWSTR, :PVOID
_WSTDIO_DEFINED equ 1
endif

.list
