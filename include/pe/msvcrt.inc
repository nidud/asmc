ifndef __LIBC_INC
 include libc.inc
endif

	.xlist

ifdef	__PE__
	option	dllimport:<msvcrt>
else
	includelib msvcrt.lib
endif

memchr		proto _CDecl :LPSTR, :SIZE_T,:SIZE_T
memcpy		proto _CDecl :LPSTR, :LPSTR, :SIZE_T
memmove		proto _CDecl :LPSTR, :LPSTR, :SIZE_T
memcmp		proto _CDecl :LPSTR, :LPSTR, :SIZE_T
memset		proto _CDecl :LPSTR, :SIZE_T,:SIZE_T
_memicmp	proto _CDecl :LPSTR, :LPSTR, :SIZE_T

strlen		proto _CDecl :LPSTR
strchr		proto _CDecl :LPSTR, :SIZE_T
strcmp		proto _CDecl :LPSTR, :LPSTR
strncmp		proto _CDecl :LPSTR, :LPSTR, :SIZE_T
strcpy		proto _CDecl :LPSTR, :LPSTR
strncpy		proto _CDecl :LPSTR, :LPSTR, :SIZE_T
strcat		proto _CDecl :LPSTR, :LPSTR
_stricmp	proto _CDecl :LPSTR, :LPSTR
_strnicmp	proto _CDecl :LPSTR, :LPSTR, :SIZE_T
_strupr		proto _CDecl :LPSTR
_strrev		proto _CDecl :LPSTR
_strlwr		proto _CDecl :LPSTR
strrchr		proto _CDecl :LPSTR, :SIZE_T
strstr		proto _CDecl :LPSTR, :LPSTR

SEEK_CUR	equ 1
SEEK_END	equ 2
SEEK_SET	equ 0

_NSTREAM_	equ 20
_MAXIOBUF	equ 4000h
_INTIOBUF	equ 1000h
_MINIOBUF	equ 0200h

_IOFBF		equ 0000h
_IOREAD		equ 0001h
_IOWRT		equ 0002h
_IONBF		equ 0004h
_IOMYBUF	equ 0008h
_IOEOF		equ 0010h
_IOERR		equ 0020h
_IOSTRG		equ 0040h
_IOLBF		equ 0040h
_IORW		equ 0080h
_IOYOURBUF	equ 0100h
_IOSETVBUF	equ 0400h
_IOFEOF		equ 0800h
_IOFLRTN	equ 1000h
_IOCTRLZ	equ 2000h
_IOCOMMIT	equ 4000h

_iobuf		STRUC SIZE_T
_ptr		LPSTR ?
_cnt		dd ?
_base		LPSTR ?
_flag		dd ?
_file		dd ?
_charbuf	dd ?
_bufsize	dd ?
_tmpfname	LPSTR ?
_iobuf		ENDS

LPFILE		TYPEDEF PTR _iobuf

_output		PROTO _CDecl :LPFILE, :LPSTR, :PVOID
sprintf		PROTO _CDecl :LPSTR, :LPSTR, :VARARG
printf		PROTO _CDecl :LPSTR, :VARARG
fprintf		PROTO _CDecl :LPFILE, :LPSTR, :VARARG
puts		PROTO _CDecl :LPSTR
fopen		PROTO _CDecl :LPSTR, :LPSTR
fclose		PROTO _CDecl :LPFILE
fgetc		PROTO _CDecl :LPFILE
vsprintf	PROTO _CDecl :LPSTR, :LPSTR, :PVOID
vfprintf	PROTO _CDecl :LPFILE,:LPSTR, :PVOID
fread		PROTO _CDecl :LPSTR, :SINT, :SINT, :LPFILE
fwrite		PROTO _CDecl :LPSTR, :SINT, :SINT, :LPFILE
fseek		PROTO _CDecl :LPFILE,:SIZE_T, :SIZE_T
fgets		PROTO _CDecl :LPSTR, :SIZE_T, :LPFILE
fputs		PROTO _CDecl :LPSTR, :LPFILE
fputc		PROTO _CDecl :SIZE_T, :LPFILE
feof		PROTO _CDecl :LPFILE
ftell		PROTO _CDecl :LPFILE
perror		PROTO _CDecl :LPSTR
fflush		PROTO _CDecl :LPFILE
rewind		PROTO _CDecl :LPFILE
_flsbuf		PROTO _CDecl :SIZE_T, :LPFILE
_freebuf	PROTO _CDecl :LPFILE
_filbuf		PROTO _CDecl :LPFILE
_getst		PROTO _CDecl
_ftbuf		PROTO _CDecl :SIZE_T, :LPFILE
_stbuf		PROTO _CDecl :LPFILE
_getbuf		PROTO _CDecl :LPFILE
setvbuf		PROTO _CDecl :LPFILE, :LPSTR, :SIZE_T, :SIZE_T
setbuf		PROTO _CDecl :LPFILE, :LPSTR

exit		proto _CDecl :SIZE_T
atoi		proto _CDecl :LPSTR
atol		proto _CDecl :LPSTR
qsort		proto _CDecl :PVOID, :SIZE_T, :SIZE_T, :PVOID

__getmainargs	proto _CDecl :ptr, :ptr, :ptr, :ptr, :ptr
__iob_func	proto

;
; ISO 8601:	YYYY-MM-DD hh:mm:ss
; Short form:	YY-MM-DD hh:mm
;
; input accept: MM/DD/YY[YY] | DD.MM.YY[YY] | [YY]YY-MM-DD
;
DT_BASEYEAR		equ 1980

_DAY_SEC		equ 24 * 60 * 60	; secs in a day
_YEAR_SEC		equ 365 * _DAY_SEC	; secs in a year
_FOUR_YEAR_SEC		equ 1461 * _DAY_SEC	; secs in a 4 year interval
_DEC_SEC		equ 315532800		; secs in 1970-1979
_BASE_YEAR		equ 70			; 1970 is the base year
_BASE_DOW		equ 4			; 01-01-70 was a Thursday
_LEAP_YEAR_ADJUST	equ 17			; Leap years 1900 - 1970
_MAX_YEAR		equ 138			; 2038 is the max year


FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS

SYSTEMTIME	STRUC
wYear		dw ?
wMonth		dw ?
wDayOfWeek	dw ?
wDay		dw ?
wHour		dw ?
wMinute		dw ?
wSecond		dw ?
wMilliseconds	dw ?
SYSTEMTIME	ENDS

S_TM		STRUC
tm_sec		dd ?	; seconds after the minute - [0,59]
tm_min		dd ?	; minutes after the hour - [0,59]
tm_hour		dd ?	; hours since midnight - [0,23]
tm_mday		dd ?	; day of the month - [1,31]
tm_mon		dd ?	; months since January - [0,11]
tm_year		dd ?	; years since 1900
tm_wday		dd ?	; days since Sunday - [0,6]
tm_yday		dd ?	; days since January 1 - [0,365]
tm_isdst	dd ?	; daylight savings time flag
S_TM		ENDS

TIME_T		TYPEDEF SDWORD
LPTIME		TYPEDEF PTR TIME_T
LPFILETIME	TYPEDEF PTR FILETIME
LPSYSTEMTIME	TYPEDEF PTR SYSTEMTIME

localtime	PROTO _CDecl :LPTIME
gmtime		PROTO _CDecl :LPTIME
_time32		PROTO _CDecl :LPTIME
_time64		PROTO _CDecl :LPTIME
_tzset		PROTO
clock		PROTO

_A_RDONLY	equ 01h
_A_HIDDEN	equ 02h
_A_SYSTEM	equ 04h
_A_VOLID	equ 08h
_A_SUBDIR	equ 10h
_A_ARCH		equ 20h
_A_NORMAL	equ 80h

_A_TEMPORARY	equ 0100h
_A_SPARSE_FILE	equ 0200h
_A_REPARSEPOINT equ 0400h
_A_COMPRESSED	equ 0800h
_A_OFFLINE	equ 1000h
_A_NOT_INDEXED	equ 2000h
_A_ENCRYPTED	equ 4000h

SEEK_SET	equ 0
SEEK_CUR	equ 1
SEEK_END	equ 2

FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS

_finddata_t	STRUC
ff_attrib	dd ?	; DWORD File attributes
ff_time_create	dd ?	; DWORD File creation time
ff_time_access	dd ?	; DWORD Last access time
ff_time_write	dd ?	; DWORD Last modification time
ff_size		dq ?	; QWORD File size
ff_name		db 260 dup(?)
_finddata_t	ENDS	; 284 byte

A_CREATE	equ 1 ; fails if exists
A_CREATETRUNC	equ 2 ; trunc if exists
A_OPEN		equ 3 ; fails if not exists
A_OPENCREATE	equ 4 ; open if exists or create
A_TRUNC		equ 5 ; fails if not exists

M_DELETE	equ 0x00010000
M_RDONLY	equ 0x80000000
M_WRONLY	equ 0x40000000
M_RDWR		equ M_RDONLY or M_WRONLY

_open		PROTO _CDecl :LPSTR, :UINT, :VARARG
_sopen		PROTO _CDecl :LPSTR, :UINT, :UINT, :VARARG
_read		PROTO _CDecl :SINT, :PVOID, :SIZE_T
_creat		PROTO _CDecl :LPSTR, :UINT
_close		PROTO _CDecl :SINT
_lseek		PROTO _CDecl :SINT, :SIZE_T, :UINT
_write		PROTO _CDecl :SINT, :PVOID, :SIZE_T
_access		PROTO _CDecl :LPSTR, :UINT
_isatty		PROTO _CDecl :SINT
_eof		PROTO _CDecl :SINT
_chsize		PROTO _CDecl :SINT, :SIZE_T
_filelength	PROTO _CDecl :SINT
_findfirst	PROTO _CDecl :LPSTR, :PTR _finddata_t
_findnext	PROTO _CDecl :HANDLE, :PTR _finddata_t
_findclose	PROTO _CDecl :HANDLE
_tell		PROTO _CDecl :SINT
_osopen		PROTO _CDecl :LPSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
_lseeki64	PROTO _CDecl :SINT, :QWORD, :UINT
remove		PROTO _CDecl :LPSTR
rename		PROTO _CDecl :LPSTR, :LPSTR

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

_getdrive	PROTO _CDecl
_chdrive	PROTO _CDecl :SINT
_chdir		PROTO _CDecl :LPSTR
_mkdir		PROTO _CDecl :LPSTR
_rmdir		PROTO _CDecl :LPSTR
_getcwd		PROTO _CDecl :LPSTR, :SINT
_getdcwd	PROTO _CDecl :SINT, :LPSTR, :SINT
_wchdir		PROTO _CDecl :LPWSTR
_wmkdir		PROTO _CDecl :LPWSTR
_wrmdir		PROTO _CDecl :LPWSTR
_wgetcwd	PROTO _CDecl :LPWSTR, :SINT
_wgetdcwd	PROTO _CDecl :SINT, :LPWSTR, :SINT

_UPPER		equ 01h		; upper case letter
_LOWER		equ 02h		; lower case letter
_DIGIT		equ 04h		; digit[0-9]
_SPACE		equ 08h		; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h		; punctuation character
_CONTROL	equ 20h		; control character
_BLANK		equ 40h		; space char
_HEX		equ 80h		; hexadecimal digit

isspace		PROTO _CDecl :SINT
isupper		PROTO _CDecl :SINT
isalpha		PROTO _CDecl :SINT
isalnum		PROTO _CDecl :SINT
isascii		PROTO _CDecl :SINT
iscntrl		PROTO _CDecl :SINT
isdigit		PROTO _CDecl :SINT
isgraph		PROTO _CDecl :SINT
islower		PROTO _CDecl :SINT
isprint		PROTO _CDecl :SINT
ispunct		PROTO _CDecl :SINT
isxdigit	PROTO _CDecl :SINT
toupper		PROTO _CDecl :SINT
tolower		PROTO _CDecl :SINT

malloc		proto _CDecl :size_t
realloc		PROTO _CDecl :ptr, :size_t
free		proto _CDecl :ptr
calloc		proto _CDecl :dword, :dword

system		proto _CDecl :ptr
getenv		proto _CDecl :ptr

.list
