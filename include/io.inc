ifndef __LIBC_INC
 include libc.inc
endif

.xlist
IFDEF __PE__
option	dllimport:<msvcrt>
ENDIF

_NFILE_		equ 20

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

FH_OPEN		equ 01h
FH_EOF		equ 02h
FH_CRLF		equ 04h
FH_PIPE		equ 08h
FH_NOINHERIT	equ 10h
FH_APPEND	equ 20h
FH_DEVICE	equ 40h
FH_TEXT		equ 80h

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

_wfinddata_t	STRUC
ff_attrib	dd ?	; DWORD File attributes
ff_time_create	dd ?	; DWORD File creation time
ff_time_access	dd ?	; DWORD Last access time
ff_time_write	dd ?	; DWORD Last modification time
ff_size		dq ?	; QWORD File size
ff_name		dw 260 dup(?)
_wfinddata_t	ENDS

externdef	_nfile:DWORD
externdef	_osfile:BYTE
externdef	_osfhnd:HANDLE
externdef	_diskflag:DWORD

A_CREATE	equ 1 ; fails if exists
A_CREATETRUNC	equ 2 ; trunc if exists
A_OPEN		equ 3 ; fails if not exists
A_OPENCREATE	equ 4 ; open if exists or create
A_TRUNC		equ 5 ; fails if not exists

M_DELETE	equ 0x00010000
M_RDONLY	equ 0x80000000
M_WRONLY	equ 0x40000000
M_RDWR		equ M_RDONLY or M_WRONLY

_open		proto _CDecl :LPSTR, :SINT, :VARARG
_sopen		proto _CDecl :LPSTR, :UINT, :UINT, :VARARG
_read		proto :SINT, :PVOID, :SIZE_T
_creat		proto :LPSTR, :UINT
_close		proto :SINT
_lseek		proto :SINT, :SIZE_T, :UINT
_write		proto :SINT, :PVOID, :SIZE_T
_access		proto :LPSTR, :UINT
_isatty		proto :SINT
_eof		proto :SINT
_chsize		proto :SINT, :SIZE_T
_filelength	proto :SINT
_findfirst	proto :LPSTR, :PTR _finddata_t
_findnext	proto :HANDLE, :PTR _finddata_t
_findclose	proto :HANDLE
_tell		proto :SINT
_lseeki64	proto :SINT, :QWORD, :UINT
remove		proto :LPSTR
rename		proto :LPSTR, :LPSTR

ifndef _WIO_DEFINED

_waccess	proto :ptr wchar_t, :SINT
_wchmod		proto :ptr wchar_t, :SINT
_wcreat		proto :ptr wchar_t, :SINT
_wfindfirst	proto :ptr wchar_t, :ptr _wfinddata_t
_wfindnext	proto :SINT, :ptr _wfinddata_t
_wunlink	proto :ptr wchar_t
_wrename	proto :ptr wchar_t, :ptr wchar_t
_wopen		proto _CDecl :ptr wchar_t, :SINT, :VARARG
_wsopen		proto _CDecl :ptr wchar_t, :SINT, :SINT, :VARARG
_wmktemp	proto :ptr wchar_t
if 0
if _INTEGRAL_MAX_BITS GE 64
_wfindfirsti64	proto :ptr wchar_t, :ptr _wfinddatai64_t
_wfindnexti64	proto :LONG, :ptr _wfinddatai64_t
endif
endif
_WIO_DEFINED	equ 1
endif

ifndef __PE__

osopenA		proto :LPSTR, :UINT, :UINT, :UINT
osopenW		proto :LPWSTR, :UINT, :UINT, :UINT
_osopenA	proto :LPSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
_osopenW	proto :LPWSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
ifdef _UNICODE
osopen		equ <osopenW>
_osopen		equ <_osopenW>
else
osopen		equ <osopenA>
_osopen		equ <_osopenA>
endif

osread		proto :SINT, :PVOID, :SIZE_T
oswrite		proto :SINT, :PVOID, :SIZE_T
getosfhnd	proto :SINT
osmaperr	proto

;;;;;;;;;;;;;;; crtl

getfattr	proto :LPSTR
_wgetfattr	proto :LPWSTR

setfattr	proto :LPTSTR, :UINT
filexist	proto :LPSTR
readword	proto :LPSTR
getftime	proto :SINT
getftime_access proto :SINT
getftime_create proto :SINT
setftime	proto :SINT, :DWORD
setftime_access proto :SINT, :DWORD
setftime_create proto :SINT, :DWORD
__FTToTime	proto :PTR FILETIME

externdef	console:DWORD
externdef	_diskflag:DWORD

endif

.list
