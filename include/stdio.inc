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

S_FILE		STRUC SIZE_T
iob_ptr		LPSTR ?
iob_cnt		dd ?
iob_base	LPSTR ?
iob_flag	dd ?
iob_file	dd ?
iob_charbuf	dd ?
iob_bufsize	dd ?
iob_tmpfname	LPSTR ?
S_FILE		ENDS
LPFILE		TYPEDEF PTR S_FILE

externdef	_bufin:BYTE
externdef	_iob:S_FILE
externdef	stdout:S_FILE
externdef	stderr:S_FILE
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
fgets		PROTO :LPSTR, :SIZE_T, :LPFILE
fputs		PROTO :LPSTR, :LPFILE
fputc		PROTO :SIZE_T, :LPFILE
feof		PROTO :LPFILE
ftell		PROTO :LPFILE
perror		PROTO :LPSTR
fflush		PROTO :LPFILE
rewind		PROTO :LPFILE
_flsbuf		PROTO :SIZE_T, :LPFILE
_freebuf	PROTO :LPFILE
_filbuf		PROTO :LPFILE
_getst		PROTO
_ftbuf		PROTO :SIZE_T, :LPFILE
_stbuf		PROTO :LPFILE
_getbuf		PROTO :LPFILE
setvbuf		PROTO :LPFILE, :LPSTR, :SIZE_T, :SIZE_T
setbuf		PROTO :LPFILE, :LPSTR

;;;;;;;;;;;;;;; kernel32.lib
IFDEF __PE__
_iobuf	equ <S_FILE>
option	dllimport:<kernel32>
ENDIF

FILE_TYPE_UNKNOWN   equ 0x0000	; The type of the specified file is unknown.
FILE_TYPE_DISK	    equ 0x0001	; The specified file is a disk file.
FILE_TYPE_CHAR	    equ 0x0002	; The specified file is a character file,
				; typically an LPT device or a console.
FILE_TYPE_PIPE	    equ 0x0003	; The specified file is either a named or
				; anonymous pipe.
FILE_TYPE_REMOTE    equ 0x8000

; DWORD
GetFileType proto _CType \
	hFile:		HANDLE	; file handle
; int
wvsprintfA proto _CType \
	lpOutput:	LPSTR,	; pointer to buffer for output
	lpFormat:	LPSTR,	; pointer to format-control string
	va_list:	PVOID	; variable list of format-control arguments
wvsprintfW proto _CType \
	lpOutput:	LPWSTR,
	lpFormat:	LPWSTR,
	va_list:	PVOID

	.list
