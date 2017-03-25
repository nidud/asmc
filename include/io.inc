ifndef __IO_INC
__IO_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifdef __PE__
option	dllimport:<msvcrt>
endif

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

ifndef _TIME_T_DEFINED
_TIME_T_DEFINED equ <>
time_t		typedef sdword
endif

_finddata_t	STRUC
ff_attrib	dd ?
ff_time_create	time_t ?	; File creation time
ff_time_access	time_t ?	; Last access time
ff_time_write	time_t ?	; Last modification time
ff_size		dq ?
ff_name		db 260 dup(?)
_finddata_t	ENDS

ifndef _WFINDDATA_T_DEFINED
_WFINDDATA_T_DEFINED equ <>
_wfinddata_t	STRUC
attrib		dd ?
time_create	time_t ?	;; -1 for FAT file systems
time_access	time_t ?	;; -1 for FAT file systems
time_write	time_t ?
_size		dq ?
_name		wchar_t 260 dup(?)
_wfinddata_t	ENDS
if _INTEGRAL_MAX_BITS GE 64
_wfinddatai64_t STRUC
attrib		dd ?
time_create	time_t ?	;; -1 for FAT file systems
time_access	time_t ?	;; -1 for FAT file systems
time_write	time_t ?
_size		dq ?
_name		wchar_t 260 dup(?)
_wfinddatai64_t ENDS
endif
endif

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
_read		proto __cdecl :SINT, :PVOID, :SIZE_T
_creat		proto __cdecl :LPSTR, :UINT
_close		proto __cdecl :SINT
_lseek		proto __cdecl :SINT, :SIZE_T, :UINT
_write		proto __cdecl :SINT, :PVOID, :SIZE_T
_access		proto __cdecl :LPSTR, :UINT
_isatty		proto __cdecl :SINT
_eof		proto __cdecl :SINT
_chsize		proto __cdecl :SINT, :SIZE_T
_filelength	proto __cdecl :SINT
_findfirst	proto __cdecl :LPSTR, :PTR _finddata_t
_findnext	proto __cdecl :HANDLE, :PTR _finddata_t
_findclose	proto __cdecl :HANDLE
_tell		proto __cdecl :SINT
_lseeki64	proto __cdecl :SINT, :QWORD, :UINT
remove		proto __cdecl :LPSTR
rename		proto __cdecl :LPSTR, :LPSTR

ifndef _WIO_DEFINED
_WIO_DEFINED equ <>
_waccess	proto __cdecl :ptr wchar_t, :SINT
_wchmod		proto __cdecl :ptr wchar_t, :SINT
_wcreat		proto __cdecl :ptr wchar_t, :SINT
_wfindfirst	proto __cdecl :ptr wchar_t, :ptr _wfinddata_t
_wfindnext	proto __cdecl :SINT, :ptr _wfinddata_t
_wunlink	proto __cdecl :ptr wchar_t
_wrename	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wopen		proto _CDecl :ptr wchar_t, :SINT, :VARARG
_wsopen		proto _CDecl :ptr wchar_t, :SINT, :SINT, :VARARG
_wmktemp	proto __cdecl :ptr wchar_t
if 0
if _INTEGRAL_MAX_BITS GE 64
_wfindfirsti64	proto __cdecl :ptr wchar_t, :ptr _wfinddatai64_t
_wfindnexti64	proto __cdecl :LONG, :ptr _wfinddatai64_t
endif
endif
endif ; _WIO_DEFINED

ifndef __PE__

osopenA		proto _CType :LPSTR, :UINT, :UINT, :UINT
osopenW		proto _CType :LPWSTR, :UINT, :UINT, :UINT
_osopenA	proto _CType :LPSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
_osopenW	proto _CType :LPWSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
ifdef _UNICODE
osopen		equ <osopenW>
_osopen		equ <_osopenW>
else
osopen		equ <osopenA>
_osopen		equ <_osopenA>
endif

osread		proto _CType :SINT, :PVOID, :SIZE_T
oswrite		proto _CType :SINT, :PVOID, :SIZE_T
getosfhnd	proto _CType :SINT
osmaperr	proto _CType

;;;;;;;;;;;;;;; crtl

getfattr	proto _CType :LPSTR
_wgetfattr	proto _CType :LPWSTR

setfattr	proto _CType :LPTSTR, :UINT
filexist	proto _CType :LPSTR
readword	proto _CType :LPSTR
getftime	proto _CType :SINT
getftime_access proto _CType :SINT
getftime_create proto _CType :SINT
setftime	proto _CType :SINT, :DWORD
setftime_access proto _CType :SINT, :DWORD
setftime_create proto _CType :SINT, :DWORD
__FTToTime	proto _CType :PTR FILETIME

externdef	console:DWORD
externdef	_diskflag:DWORD

endif ; __PE__

.list
endif ; __IO_INC
