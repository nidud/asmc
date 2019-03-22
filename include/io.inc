.pragma list(push, 0)
ifndef __IO_INC
__IO_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc, msvcrt)

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

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

ifndef LPFILETIME
FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
LPFILETIME	typedef ptr FILETIME
endif

ifndef _TIME_T_DEFINED
_TIME_T_DEFINED equ <>
ifdef _WIN64
time_t		typedef sqword
else
time_t		typedef sdword
endif
endif

_finddata_t	STRUC
attrib		dd ?
time_create	time_t ?	; File creation time
time_access	time_t ?	; Last access time
time_write	time_t ?	; Last modification time
_size		size_t ?
_name		db 260 dup(?)
_finddata_t	ENDS

ifndef _WFINDDATA_T_DEFINED
_WFINDDATA_T_DEFINED equ <>
_wfinddata_t	STRUC
attrib		dd ?
time_create	time_t ?	;; -1 for FAT file systems
time_access	time_t ?	;; -1 for FAT file systems
time_write	time_t ?
_size		size_t ?
_name		wchar_t 260 dup(?)
_wfinddata_t	ENDS
if _INTEGRAL_MAX_BITS GE 64
_wfinddatai64_t STRUC
attrib		dd ?
time_create	dq ?
time_access	dq ?
time_write	dq ?
_size		dq ?
_name		wchar_t 260 dup(?)
_wfinddatai64_t ENDS
endif
endif

externdef	_nfile:DWORD
externdef	_osfile:BYTE
externdef	_osfhnd:HANDLE
ifdef __DZ__
externdef	_diskflag:DWORD
endif

A_CREATE	equ 1 ; fails if exists
A_CREATETRUNC	equ 2 ; trunc if exists
A_OPEN		equ 3 ; fails if not exists
A_OPENCREATE	equ 4 ; open if exists or create
A_TRUNC		equ 5 ; fails if not exists

M_DELETE	equ 0x00010000
M_RDONLY	equ 0x80000000
M_WRONLY	equ 0x40000000
M_RDWR		equ M_RDONLY or M_WRONLY

if 0
open		proto _CDecl :LPSTR, :SINT, :VARARG
read		proto __cdecl :SINT, :PVOID, :SIZE_T
close		proto __cdecl :SINT
filelength	proto __cdecl :SINT
endif

_open		proto _CDecl :LPSTR, :SINT, :VARARG
_sopen		proto _CDecl :LPSTR, :UINT, :UINT, :VARARG
_read		proto __cdecl :SINT, :PVOID, :SIZE_T
_creat		proto __cdecl :LPSTR, :UINT
_close		proto __cdecl :SINT
_lseek		proto __cdecl :SINT, :SIZE_T, :UINT
_write		proto __cdecl :SINT, :PVOID, :UINT
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

__lock_fhandle	proto __cdecl :int_t
_unlock_fhandle proto __cdecl :int_t

ifdef _CRTBLD
ifndef _NOT_CRTL_BUILD_
_chsize_nolock	proto __cdecl :int_t, :int64_t
_close_nolock	proto __cdecl :int_t
_lseek_nolock	proto __cdecl :int_t, :long_t, :int_t
_setmode_nolock proto __cdecl :int_t, :int_t
_read_nolock	proto __cdecl :int_t, :ptr, :uint_t
_write_nolock	proto __cdecl :int_t, :ptr, :uint_t
_lseeki64_nolock proto __cdecl :int_t, :int64_t, :int_t
if defined (_CRT_DISABLE_PERFCRIT_LOCKS) and not defined (_DLL)
_chsize		equ <_chsize_nolock>
_close		equ <_close_nolock>
_lseek		equ <_lseek_nolock>
_setmode	equ <_setmode_nolock>
_read		equ <_read_nolock>
_write		equ <_write_nolock>
_lseeki64	equ <_lseeki64_nolock>
endif
endif ;; _NOT_CRTL_BUILD_
endif ;; _CRTBLD

_get_osfhandle	proto __cdecl :int_t
_open_osfhandle proto __cdecl :intptr_t, :int_t

ifndef __PE__
_osopenA	proto __cdecl :LPSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
_osopenW	proto __cdecl :LPWSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
ifdef _UNICODE
_osopen		equ <_osopenW>
else
_osopen		equ <_osopenA>
endif
osread		proto __cdecl :SINT, :PVOID, :SIZE_T
oswrite		proto __cdecl :SINT, :PVOID, :SIZE_T
getosfhnd	proto __cdecl :SINT
osmaperr	proto __cdecl
getfattr	proto __cdecl :LPSTR
_wgetfattr	proto __cdecl :LPWSTR
endif ; __PE__

.pragma pack(pop)
endif
.pragma list(pop)
