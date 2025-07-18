ifndef __WCHAR_INC
define __WCHAR_INC
.pragma list(push, 0)
ifndef _WINDEF_
 include windef.inc
endif

ifndef _WIN32
ifndef _WIN64
.err <ERROR: Only Win64 or Win32 targets supported>
endif
endif

.pragma comment(lib, libc, msvcrt)

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef sqword
else
time_t typedef sdword
endif
endif

WCHAR_MIN	equ 0
WCHAR_MAX	equ 0xFFFF

ifndef _VA_LIST_DEFINED
define _VA_LIST_DEFINED
ifdef  _M_ALPHA
va_list		STRUC
a0		LPSTR ?
offset		SINT ?
va_list		ENDS
else
va_list		typedef LPSTR
endif
endif

ifndef WEOF
WEOF		equ 0xFFFF
endif

ifndef _FILE_DEFINED
define _FILE_DEFINED
_iobuf		struct size_t
_ptr		string_t ?
_cnt		int_t ?
_base		string_t ?
_flag		int_t ?
_file		int_t ?
_charbuf	int_t ?
_bufsiz		int_t ?
union
 struct
  _bitcnt	int_t ?
  _crc32	int_t ?
 ends
 _tmpfname	string_t ?
ends
_iobuf		ends
FILE		typedef _iobuf
LPFILE		typedef ptr _iobuf
endif

ifndef _STDIO_DEFINED
ifdef _LIBCMT
_iob		equ <[__acrt_iob_func(0)]>
elseif defined(_MSVCRT) and not defined(_CRTBLD)
_iob		equ <[__iob_func()]>
else
externdef	_iob:_iobuf
endif
endif

ifndef _FSIZE_T_DEFINED
define _FSIZE_T_DEFINED
_fsize_t	typedef size_t
endif

ifndef _WFINDDATA_T_DEFINED
define _WFINDDATA_T_DEFINED
_wfinddata_t	STRUC
attrib		dd ?
time_create	time_t ?
time_access	time_t ?
time_write	time_t ?
size		_fsize_t ?
name		wchar_t 260 dup(?)
_wfinddata_t	ENDS
if _INTEGRAL_MAX_BITS GE 64
_wfinddatai64_t STRUC
attrib		dd ?
time_create	time_t ?
time_access	time_t ?
time_write	time_t ?
size		_fsize_t ?
name		wchar_t 260 dup(?)
_wfinddatai64_t ENDS
endif
endif


ifndef NULL
NULL		equ 0
endif


ifndef _CTYPE_DISABLE_MACROS
externdef	_ctype:word
externdef	_pctype:ptr word
externdef	_pwctype:ptr wctype_t
endif

_UPPER		equ 0x1
_LOWER		equ 0x2
_DIGIT		equ 0x4
_SPACE		equ 0x8
_PUNCT		equ 0x10
_CONTROL	equ 0x20
_BLANK		equ 0x40
_HEX		equ 0x80

_LEADBYTE	equ 0x8000
_ALPHA		equ 0x0100 OR _UPPER OR _LOWER

ifndef _WCTYPE_DEFINED

iswalpha	proto __cdecl :wint_t
iswupper	proto __cdecl :wint_t
iswlower	proto __cdecl :wint_t
iswdigit	proto __cdecl :wint_t
iswxdigit	proto __cdecl :wint_t
iswspace	proto __cdecl :wint_t
iswpunct	proto __cdecl :wint_t
iswalnum	proto __cdecl :wint_t
iswprint	proto __cdecl :wint_t
iswgraph	proto __cdecl :wint_t
iswcntrl	proto __cdecl :wint_t
iswascii	proto __cdecl :wint_t
isleadbyte	proto __cdecl :SINT

towupper	proto __cdecl :wchar_t
towlower	proto __cdecl :wchar_t

iswctype	proto __cdecl :wint_t, :wctype_t

_WCTYPE_DEFINED equ 1
endif

ifndef _WDIRECT_DEFINED
define _WDIRECT_DEFINED
_wchdir		proto __cdecl :wstring_t
_wgetcwd	proto __cdecl :wstring_t, :int_t
_wgetdcwd	proto __cdecl :int_t, :wstring_t, :int_t
_wmkdir		proto __cdecl :wstring_t
_wrmdir		proto __cdecl :wstring_t
endif

ifndef _WIO_DEFINED
define _WIO_DEFINED
_waccess	proto __cdecl :wstring_t, :int_t
_wchmod		proto __cdecl :wstring_t, :int_t
_wcreat		proto __cdecl :wstring_t, :int_t
_wfindfirst	proto __cdecl :wstring_t, :ptr _wfinddata_t
_wfindnext	proto __cdecl :ptr, :ptr _wfinddata_t
_wunlink	proto __cdecl :wstring_t
_wrename	proto __cdecl :wstring_t, :wstring_t
_wopen		proto __Cdecl :wstring_t, :int_t, :vararg
_wsopen		proto __Cdecl :wstring_t, :int_t, :int_t, :vararg
_wmktemp	proto __cdecl :wstring_t
if _INTEGRAL_MAX_BITS GE 64
_wfindfirsti64	proto __cdecl :wstring_t, :ptr _wfinddatai64_t
_wfindnexti64	proto __cdecl :ptr, :ptr _wfinddatai64_t
endif
endif

ifndef _WLOCALE_DEFINED
define _WLOCALE_DEFINED
_wsetlocale	proto __cdecl :SINT, :ptr wchar_t
endif

ifndef _WPROCESS_DEFINED
define _WPROCESS_DEFINED

_wexecl		proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexecle	proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexeclp	proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexeclpe	proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexecv		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wexecve	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wexecvp	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wexecvpe	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wspawnl	proto __Cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnle	proto __Cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnlp	proto __Cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnlpe	proto __Cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnv	proto __cdecl :SINT, :ptr wchar_t, :ptr wchar_t
_wspawnve	proto __cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wspawnvp	proto __cdecl :SINT, :ptr wchar_t, :ptr wchar_t
_wspawnvpe	proto __cdecl :SINT, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wsystem	proto __cdecl :ptr wchar_t
endif

ifndef _WCTYPE_DEFINED
ifndef _WCTYPE_INLINE_DEFINED
define _WCTYPE_INLINE_DEFINED

iswalpha macro _c
	exitm<iswctype(_c,_APHA)>
	endm
iswupper macro _c
	exitm<iswctype(_c,_UPPER)>
	endm
iswlower macro _c
	exitm<iswctype(_c,_LOWER)>
	endm
iswdigit macro _c
	exitm<iswctype(_c,_DIGIT)>
	endm
iswxdigit macro _c
	exitm<iswctype(_c,_HEX)>
	endm
iswspace macro _c
	exitm<iswctype(_c,_SPACE)>
	endm
iswpunct macro _c
	exitm<iswctype(_c,_PUNCT)>
	endm
iswalnum macro _c
	exitm<iswctype(_c,_APHA OR _DIGIT)>
	endm
iswprint macro _c
	exitm<iswctype(_c,_BLANK OR _PUNCT OR _APHA OR _DIGIT)>
	endm
iswgraph macro _c
	exitm<iswctype(_c,_PUNCT OR _APHA OR _DIGIT)>
	endm
iswcntrl macro _c
	exitm<iswctype(_c,_CONTROL)>
	endm
iswascii macro _c
	exitm<_c LT 0x80>
	endm

ifndef _CTYPE_DISABLE_MACROS
isleadbyte macro _c
	exitm<_pctype[_c] AND _LEADBYTE>
	endm
endif
endif
endif

ifndef _POSIX_

ifndef _INO_T_DEFINED
define _INO_T_DEFINED
_ino_t typedef word
endif
ifndef _DEV_T_DEFINED
define _DEV_T_DEFINED
_dev_t typedef dword
endif

ifndef _OFF_T_DEFINED
define _OFF_T_DEFINED
_off32_t typedef sdword
_off64_t typedef qword
ifdef _WIN64
_off_t typedef qword
else
_off_t typedef sdword
endif
if not __STDC__
off_t	typedef _off_t
off32_t typedef sdword
off64_t typedef qword
endif
endif

ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef sdword
endif

ifndef _STAT_DEFINED
define _STAT_DEFINED

.pragma pack(push, size_t)

.template _stat32
ifdef __UNIX__
    st_dev	dq ?	    ; 0
    st_ino	size_t ?    ; 8
 ifdef _WIN64
    st_nlink	dq ?	    ; 16
    st_mode	dd ?	    ; 24
 else
    st_mode	dd ?	    ; 16
    st_nlink	dd ?	    ; 20
 endif
    st_uid	dd ?	    ; 24/28
    st_gid	dd ?	    ; 28/32
    st_rdev	dq ?	    ; 32/40
    st_size	size_t ?    ; 44/48
    st_blksize	size_t ?    ; 48/56
    st_blocks	size_t ?    ; 52/64
    st_atime	size_t ?    ; 56/72
    st_atimesec size_t ?    ; 60/80
    st_mtime	size_t ?    ; 64/88
    st_mtimesec size_t ?    ; 68/96
    st_ctime	size_t ?    ; 72/104
    st_ctimesec size_t ?    ; 76/112
 ifdef _WIN64
    st_reserved db 8 dup(?) ; 88
 else
    st_reserved db 24 dup(?); 144
 endif
else
    st_dev	dd ?	    ; 0
    st_ino	dw ?	    ; 4
    st_mode	dw ?	    ; 6
    st_nlink	sword ?	    ; 8
    st_uid	sword ?	    ; 10
    st_gid	sword ?	    ; 12
    st_rdev	dd ?	    ; 16
    st_size	dd ?	    ; 20
    st_atime	size_t ?    ; 24
    st_mtime	size_t ?    ; 28/32
    st_ctime	size_t ?    ; 32/40
endif
   .ends

.template _stati64
ifdef __UNIX__
    st_dev	dq ?	    ; 0
    st_ino	dq ?	    ; 8
    st_nlink	dq ?	    ; 16
    st_mode	dd ?	    ; 24
    st_uid	dd ?	    ; 28
    st_gid	dd ?	    ; 32
    st_pad	dd ?	    ; 36
    st_rdev	dq ?	    ; 40
    st_size	dq ?	    ; 48
    st_blksize	dq ?	    ; 56
    st_blocks	dq ?	    ; 64
    st_atime	dq ?	    ; 72
    st_atimesec dq ?	    ; 80
    st_mtime	dq ?	    ; 88
    st_mtimesec dq ?	    ; 96
    st_ctime	dq ?	    ; 104
    st_ctimesec dq ?	    ; 112
    st_reserved db 24 dup(?)
else
    st_dev	dd ?	    ; 0
    st_ino	dw ?	    ; 4
    st_mode	dw ?	    ; 6
    st_nlink	sword ?	    ; 8
    st_uid	sword ?	    ; 10
    st_gid	sword ?	    ; 12
    st_rdev	dd ?	    ; 16
    st_size	dq ?	    ; 24
    st_atime	dq ?	    ; 32
    st_mtime	dq ?	    ; 40
    st_ctime	dq ?	    ; 48
endif
   .ends

.pragma pack(pop)

endif

ifndef _WSTAT_DEFINED
define _WSTAT_DEFINED
_wstat		proto __cdecl :ptr wchar_t, :ptr _stat32
if _INTEGRAL_MAX_BITS GE 64
_wstat64	proto __cdecl :ptr wchar_t, :ptr _stati64
endif
endif

endif

ifndef _WSTDIO_DEFINED
define _WSTDIO_DEFINED

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
fwprintf	proto __Cdecl :ptr FILE, :ptr wchar_t, :VARARG
wprintf		proto __Cdecl :ptr wchar_t, :VARARG
_snwprintf	proto __Cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :VARARG
swprintf	proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
vfwprintf	proto __cdecl :ptr FILE, :ptr wchar_t, :PVOID
vwprintf	proto __cdecl :ptr wchar_t, :PVOID
_vsnwprintf	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :PVOID
vswprintf	proto __cdecl :ptr wchar_t, :ptr wchar_t, :PVOID
fwscanf		proto __Cdecl :ptr FILE, :ptr wchar_t, :VARARG
swscanf		proto __Cdecl :ptr wchar_t, :ptr wchar_t, :VARARG
wscanf		proto __Cdecl :ptr wchar_t, :VARARG
if 0
getwchar macro
	exitm<fgetwc(stdin)>
	endm
putwchar macro _c
	exitm<fputwc(_c,stdout)>
	endm

getwc	macro _stm
	exitm<fgetwc(_stm)>
	endm
putwc	macro _c,_stm
	exitm<fputwc(_c,_stm)>
	endm
endif
_wfdopen	proto __cdecl :SINT, :ptr wchar_t
_wfopen		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wfreopen	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr FILE
_wperror	proto __cdecl :ptr wchar_t
_wpopen		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wremove	proto __cdecl :ptr wchar_t
_wtempnam	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wtmpnam	proto __cdecl :ptr wchar_t
endif

ifndef _WSTDLIB_DEFINED
define _WSTDLIB_DEFINED
_itow		proto __cdecl :SINT, :ptr wchar_t, :SINT
_ltow		proto __cdecl :LONG, :ptr wchar_t, :SINT
_ultow		proto __cdecl :DWORD, :ptr wchar_t, :SINT
wcstod		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcstol		proto __cdecl :ptr wchar_t, :ptr wchar_t, :SINT
wcstoul		proto __cdecl :ptr wchar_t, :ptr wchar_t, :SINT
_wgetenv	proto __cdecl :ptr wchar_t
_wsystem	proto __cdecl :ptr wchar_t
_wtoi		proto __cdecl :ptr wchar_t
_wtol		proto __cdecl :ptr wchar_t
if _INTEGRAL_MAX_BITS GE 64
_i64tow		proto __cdecl :qword, :ptr wchar_t, :SINT
_ui64tow	proto __cdecl :sqword, :ptr wchar_t, :SINT
_wtoi64		proto __cdecl :ptr wchar_t
endif
endif

ifndef _POSIX_

ifndef _WSTDLIBP_DEFINED
define _WSTDLIBP_DEFINED
_wfullpath	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
_wmakepath	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wperror	proto __cdecl :ptr wchar_t
_wputenv	proto __cdecl :ptr wchar_t
_wsearchenv	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wsplitpath	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
endif

endif

ifndef _WSTRING_DEFINED
define _WSTRING_DEFINED

wcscat		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcschr		proto __cdecl :ptr wchar_t, :wchar_t
wcscmp		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscpy		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscspn		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcslen		proto __cdecl :ptr wchar_t
wcsncat		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsncmp		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsncpy		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcspbrk		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsrchr		proto __cdecl :ptr wchar_t, :wchar_t
wcsspn		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsstr		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcstok		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsdup		proto __cdecl :ptr wchar_t
_wcsicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsnicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnset	proto __cdecl :ptr wchar_t, :wchar_t, :size_t
_wcsrev		proto __cdecl :ptr wchar_t
_wcsset		proto __cdecl :ptr wchar_t, :wchar_t
_wcslwr		proto __cdecl :ptr wchar_t
_wcsupr		proto __cdecl :ptr wchar_t
wcsxfrm		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcscoll		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsncoll	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t

wcswcs		equ <wcsstr>

if NOT __STDC__
wcsdup		proto __cdecl :ptr wchar_t
wcsicmp		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsnicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsnset		proto __cdecl :ptr wchar_t, :wchar_t, :size_t
wcsrev		proto __cdecl :ptr wchar_t
wcsset		proto __cdecl :ptr wchar_t, :wchar_t
wcslwr		proto __cdecl :ptr wchar_t
wcsupr		proto __cdecl :ptr wchar_t
wcsicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t
endif
endif

ifndef _TM_DEFINED
define _TM_DEFINED
tm		STRUC
tm_sec		SINT ?
tm_min		SINT ?
tm_hour		SINT ?
tm_mday		SINT ?
tm_mon		SINT ?
tm_year		SINT ?
tm_wday		SINT ?
tm_yday		SINT ?
tm_isdst	SINT ?
tm		ENDS
endif

ifndef _WTIME_DEFINED
define _WTIME_DEFINED
_wasctime	proto __cdecl :ptr tm
_wctime		proto __cdecl :ptr time_t
wcsftime	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :ptr tm
_wstrdate	proto __cdecl :ptr wchar_t
_wstrtime	proto __cdecl :ptr wchar_t
endif

mbstate_t	typedef SINT
_Wint_t		typedef wchar_t

btowc		proto __cdecl :SINT
mbrlen		proto __cdecl :LPSTR, :size_t, :ptr mbstate_t
mbrtowc		proto __cdecl :ptr wchar_t, :LPSTR, :size_t, :ptr mbstate_t
mbsrtowcs	proto __cdecl :ptr wchar_t, :LPSTR, :size_t, :ptr mbstate_t

wcrtomb		proto __cdecl :LPSTR, :wchar_t, :ptr mbstate_t
wcsrtombs	proto __cdecl :LPSTR, :ptr wchar_t, :size_t, :ptr mbstate_t
wctob		proto __cdecl :wint_t

wmemchr		proto __cdecl :ptr, :int_t, :size_t
wmemcpy		proto __cdecl :ptr, :ptr, :size_t
wmemmove	proto __cdecl :ptr, :ptr, :size_t
wmemcmp		proto __cdecl :ptr, :ptr, :size_t
wmemset		proto __cdecl :ptr, :int_t, :size_t

.pragma list(pop)
endif
