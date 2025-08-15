.pragma list(push, 0)
ifndef __IO_INC
define __IO_INC
include libc.inc

.pragma comment(lib, libc, msvcrt)

ifndef _TIME64_T_DEFINED
define _TIME64_T_DEFINED
__time64_t typedef sqword
endif

ifdef _CRTBLD

ioinfo		STRUC
ifndef __UNIX__
osfhnd		intptr_t ?	; underlying OS file HANDLE
endif
osfile		char_t ?	; attibutes of file (e.g., open in text mode?)
pipech		char_t ?	; one char buffer for handles opened on pipes
textmode	char_t ?	; __IOINFO_TM_ANSI or __IOINFO_TM_UTF8 or __IOINFO_TM_UTF16LE
ifndef __UNIX__
unicode		char_t ?	; Was the file opened as unicode?
pipech2		char_t 2 dup(?) ; 2 more peak ahead chars for UNICODE mode
dbcsBuffer	char_t ?	; Buffer for the lead byte of dbcs when converting from dbcs to unicode
startpos	int64_t ?	; File position that matches buffer start
utf8translations int_t ?	; Buffer contains translations other than CRLF
dbcsBufferUsed	int_t ?		; Bool for the lead byte buffer is used or not
endif
ioinfo		ENDS
pioinfo		typedef ptr ioinfo

externdef	__pioinfo:pioinfo

_pioinfo proto fastcall fh:abs {
    imul eax,fh,ioinfo
    add	 rax,__pioinfo
    }

ifdef _M_IX86_16
externdef _osfile:char_t
else
_osfile macro fh
    exitm <[_pioinfo(fh)].ioinfo.osfile>
    endm
endif
_textmode macro fh
    exitm <[_pioinfo(fh)].ioinfo.textmode>
    endm
_osfhnd macro fh
    exitm <[_pioinfo(fh)].ioinfo.osfhnd>
    endm
_pipech macro fh
    exitm <[_pioinfo(fh)].ioinfo.pipech>
    endm
_pipech2 macro fh
    exitm <[_pioinfo(fh)].ioinfo.pipech2>
    endm
_tm_unicode macro fh
    exitm <[_pioinfo(fh)].ioinfo.unicode>
    endm
_startpos macro fh
    exitm <[_pioinfo(fh)].ioinfo.startpos>
    endm
_utf8translations macro fh
    exitm <[_pioinfo(fh)].ioinfo.utf8translations>
    endm
_dbcsBuffer macro fh
    exitm <[_pioinfo(fh)].ioinfo.dbcsBuffer>
    endm
_dbcsBufferUsed macro fh
    exitm <[_pioinfo(fh)].ioinfo.dbcsBufferUsed>
    endm

endif

ifdef _M_IX86_16
define _NFILE_		20
else
define _NFILE_		64
endif

; File Attribute Constants for _findfirst()

define _A_NORMAL	0x00
define _A_RDONLY	0x01
define _A_HIDDEN	0x02
define _A_SYSTEM	0x04
define _A_VOLID		0x08
define _A_SUBDIR	0x10
define _A_ARCH		0x20

; File Attribute Constants for APIs (winnt.inc)

define _FA_READONLY	0x00000001
define _FA_HIDDEN	0x00000002
define _FA_SYSTEM	0x00000004
define _FA_DIRECTORY	0x00000010
define _FA_ARCHIVE	0x00000020
define _FA_DEVICE	0x00000040
define _FA_NORMAL	0x00000080
define _FA_TEMPORARY	0x00000100
define _FA_SPARSEFILE	0x00000200
define _FA_REPARSEPOINT 0x00000400
define _FA_COMPRESSED	0x00000800
define _FA_OFFLINE	0x00001000
define _FA_NOTINDEXED	0x00002000
define _FA_ENCRYPTED	0x00004000
define _FA_INTEGRITYSTR 0x00008000
define _FA_VIRTUAL	0x00010000
define _FA_NOSCRUBDATA	0x00020000
define _FA_EA		0x00040000 ; extended attributes
define _FA_PINNED	0x00080000
define _FA_UNPINNED	0x00100000

define FOPEN		0x01
define FEOFLAG		0x02
define FCRLF		0x04
define FPIPE		0x08
define FNOINHERIT	0x10
define FAPPEND		0x20
define FDEV		0x40
define FTEXT		0x80

define SEEK_SET		0
define SEEK_CUR		1
define SEEK_END		2

ifndef LPFILETIME
FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
LPFILETIME	typedef ptr FILETIME
endif

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t		typedef sqword
else
time_t		typedef sdword
endif
endif

.pragma pack(push, size_t)

_finddata_t	STRUC
attrib		uint_t ?
time_create	time_t ?	; File creation time
time_access	time_t ?	; Last access time
time_write	time_t ?	; Last modification time
size		uint_t ?
name		char_t 260 dup(?)
_finddata_t	ENDS

_finddatai64_t	STRUC
attrib		uint_t ?
time_create	time_t ?	; File creation time
time_access	time_t ?	; Last access time
time_write	time_t ?	; Last modification time
size		uint64_t ?
name		char_t 260 dup(?)
_finddatai64_t	ENDS

ifndef _WFINDDATA_T_DEFINED
define _WFINDDATA_T_DEFINED
_wfinddata_t	STRUC
attrib		uint_t ?
time_create	time_t ?	;; -1 for FAT file systems
time_access	time_t ?	;; -1 for FAT file systems
time_write	time_t ?
size		uint_t ?
name		wchar_t 260 dup(?)
_wfinddata_t	ENDS
if _INTEGRAL_MAX_BITS GE 64
_wfinddatai64_t STRUC
attrib		uint_t ?
time_create	time_t ?
time_access	time_t ?
time_write	time_t ?
size		uint64_t ?
name		wchar_t 260 dup(?)
_wfinddatai64_t ENDS
endif
endif

.pragma pack(pop)

externdef	_nfile:uint_t


define __IOINFO_TM_ANSI	   0
define __IOINFO_TM_UTF8	   1
define __IOINFO_TM_UTF16LE 2

A_CREATE	equ 1 ; fails if exists
A_CREATETRUNC	equ 2 ; trunc if exists
A_OPEN		equ 3 ; fails if not exists
A_OPENCREATE	equ 4 ; open if exists or create
A_TRUNC		equ 5 ; fails if not exists

M_DELETE	equ 0x00010000
M_RDONLY	equ 0x80000000
M_WRONLY	equ 0x40000000
M_RDWR		equ M_RDONLY or M_WRONLY

ifdef __UNIX__

define _chsize	<ftruncate>
define _open	<open>
define _close	<close>
define _read	<read>
define _write	<write>
define _lseek	<lseek>
define _creat	<creat>
define _isatty	<isatty>
define _unlink	<unlink>
define _chmod	<chmod>
define _access	<access>

fchmod		proto __cdecl :int_t, :int_t

endif

_open		proto __Cdecl :string_t, :int_t, :vararg
_sopen		proto __Cdecl :string_t, :int_t, :int_t, :vararg
_read		proto __cdecl :int_t, :ptr, :size_t
_creat		proto __cdecl :string_t, :int_t
_close		proto __cdecl :int_t
ifdef _WIN64
_lseek		proto __cdecl :int_t, :size_t, :uint_t
else
_lseek		proto __cdecl :int_t, :dword, :uint_t
endif
_write		proto __cdecl :int_t, :ptr, :uint_t
_access		proto __cdecl :string_t, :int_t
_chmod		proto __cdecl :string_t, :int_t
_isatty		proto __cdecl :int_t
_eof		proto __cdecl :int_t
_chsize		proto __cdecl :int_t, :size_t
_filelength	proto __cdecl :int_t
_findfirst	proto __cdecl :string_t, :ptr _finddata_t
_findnext	proto __cdecl :ptr, :ptr _finddata_t
_findclose	proto __cdecl :ptr
_tell		proto __cdecl :int_t
remove		proto __cdecl :string_t
rename		proto __cdecl :string_t, :string_t
_unlink		proto __cdecl :string_t
_lseeki64	proto __cdecl :int_t, :uint64_t, :uint_t
_telli64	proto __cdecl :int_t
_filelengthi64	proto __cdecl :int_t
_findfirsti64	proto __cdecl :string_t, :ptr _finddatai64_t
_findnexti64	proto __cdecl :ptr, :ptr _finddatai64_t
_pipe		proto __cdecl :ptr int_t, :uint_t, :int_t
_dup		proto __cdecl :int_t
_dup2		proto __cdecl :int_t, :int_t
_commit		proto __cdecl :int_t
_mktemp		proto __cdecl :string_t
_mktemp_s	proto __cdecl :string_t, :size_t

ifndef _WIO_DEFINED
define _WIO_DEFINED
_waccess	proto __cdecl :wstring_t, :int_t
_wchmod		proto __cdecl :wstring_t, :int_t
_wcreat		proto __cdecl :wstring_t, :int_t
_wfindfirst	proto __cdecl :wstring_t, :ptr _wfinddata_t
_wfindnext	proto __cdecl :ptr, :ptr _wfinddata_t
_wunlink	proto __cdecl :wstring_t
_wremove	proto __cdecl :wstring_t
_wrename	proto __cdecl :wstring_t, :wstring_t
_wopen		proto __Cdecl :wstring_t, :int_t, :vararg
_wsopen		proto __Cdecl :wstring_t, :int_t, :int_t, :vararg
_wmktemp	proto __cdecl :wstring_t
_wmktemp_s	proto __cdecl :wstring_t, :size_t
if _INTEGRAL_MAX_BITS GE 64
_wfindfirsti64	proto __cdecl :wstring_t, :ptr _wfinddatai64_t
_wfindnexti64	proto __cdecl :ptr, :ptr _wfinddatai64_t
endif
endif ; _WIO_DEFINED

__lock_fhandle	proto __cdecl :int_t
_unlock_fhandle proto __cdecl :int_t

ifdef _CRTBLD
ifndef _NOT_CRTL_BUILD_
_chsize_nolock	proto __cdecl :int_t, :int64_t
_close_nolock	proto __cdecl :int_t
_lseek_nolock	proto __cdecl :int_t, :int_t, :int_t
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
else
_setmode	proto __cdecl :int_t, :int_t
endif
endif ;; _NOT_CRTL_BUILD_
else
_setmode	proto __cdecl :int_t, :int_t
endif ;; _CRTBLD

_get_osfhandle	proto __cdecl :int_t
_open_osfhandle proto __cdecl :intptr_t, :int_t
_alloc_osfhnd	proto __cdecl
_set_osfhnd	proto __cdecl :int_t, :intptr_t

if not defined(_MSVCRT) or defined(_CRTBLD)

osread		proto __cdecl :int_t, :ptr, :uint_t
oswrite		proto __cdecl :int_t, :ptr, :uint_t
osopen		proto __cdecl :LPSTR, :uint_t, :uint_t, :uint_t

getftime	proto __cdecl :int_t
getftime_access proto __cdecl :int_t
getftime_create proto __cdecl :int_t
setftime	proto __cdecl :int_t, :uint_t
setftime_access proto __cdecl :int_t, :uint_t
setftime_create proto __cdecl :int_t, :uint_t
getfattr	proto __cdecl :LPSTR
setfattr	proto __cdecl :LPSTR, :UINT
filexist	proto __cdecl :LPSTR

_wosopen	proto __cdecl :LPWSTR, :uint_t, :uint_t, :uint_t
_wgetfattr	proto __cdecl :LPWSTR
_wsetfattr	proto __cdecl :LPWSTR, :UINT
_wfilexist	proto __cdecl :LPWSTR

endif ; _MSVCRT


endif
.pragma list(pop)
