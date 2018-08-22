ifndef __STDLIB_INC
__STDLIB_INC equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
ifdef __PE__
option	dllimport:<msvcrt>
endif
;
; Maximum number of bytes in multi-byte character in the current locale
; (also defined in ctype.h).
;
ifndef MB_CUR_MAX
MB_CUR_MAX equ <__mb_cur_max>
externdef __mb_cur_max:dword
endif

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

ifndef __PE__
externdef	__argc:dword
externdef	__argv:SIZE_T
externdef	_environ:SIZE_T
externdef	_pgmptr:SIZE_T
endif

abort		proto __cdecl
exit		proto __cdecl :DWORD
atol		proto __cdecl :LPSTR
_atoi64		proto __cdecl :LPSTR
mbtowc		proto __cdecl :LPWSTR, :LPSTR, :SIZE_T
mbstowcs	proto __cdecl :LPWSTR, :LPSTR, :SIZE_T
wctomb		proto __cdecl :LPSTR, :wchar_t

QSORTCMD_T	typedef proto __cdecl :PVOID, :PVOID
LPQSORTCMD	typedef ptr QSORTCMD_T
qsort		proto :PVOID, :SIZE_T, :SIZE_T, :LPQSORTCMD
qsort4		proto :PVOID, :SIZE_T, :LPQSORTCMD

rand		proto __cdecl
rand_s		proto __cdecl :ptr UINT
srand		proto __cdecl :UINT

getenv		proto __cdecl :LPSTR
strtod		proto __cdecl :LPSTR, :LPSTR
_strtold	proto __cdecl :LPSTR, :LPSTR
_strtoq		proto __cdecl :ptr, :LPSTR, :LPSTR
strtoqd		proto __cdecl :LPSTR, :LPSTR
system		proto __cdecl :LPSTR
malloc		proto __cdecl :SIZE_T
realloc		proto __cdecl :PVOID, :SIZE_T
free		proto __cdecl :PVOID
setargv		proto __cdecl :ptr, :ptr sbyte
_makepath	proto __cdecl :LPSTR, :LPSTR, :LPSTR, :LPSTR, :LPSTR
if 0 ; use intrin.inc
_rotl		proto __cdecl :UINT, :SINT
_rotr		proto __cdecl :UINT, :SINT
_lrotl		proto __cdecl :ULONG, :SINT
_lrotr		proto __cdecl :ULONG, :SINT
endif
ifndef _WSTDLIB_DEFINED
_WSTDLIB_DEFINED equ <>

ifndef _WCHAR_T_DEFINED
_WCHAR_T_DEFINED equ <>
wchar_t		typedef WORD
endif

ifndef _WCTYPE_T_DEFINED
_WCTYPE_T_DEFINED equ <>
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
endif

ifndef __PE__
externdef	__wargv:SIZE_T
externdef	_wenviron:SIZE_T
externdef	_wpgmptr:SIZE_T
endif

_itow		proto __cdecl :SINT, :ptr wchar_t, :SINT
_ltow		proto __cdecl :SINT, :ptr wchar_t, :SINT
_ultow		proto __cdecl :DWORD, :ptr wchar_t, :SINT
wcstod		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcstol		proto __cdecl :ptr wchar_t, :ptr wchar_t, :SINT
wcstoul		proto __cdecl :ptr wchar_t, :ptr wchar_t, :SINT
_wgetenv	proto __cdecl :ptr wchar_t
_wsystem	proto __cdecl :ptr wchar_t
_wtoi		proto __cdecl :ptr wchar_t
_wtol		proto __cdecl :ptr wchar_t
setwargv	proto __cdecl :ptr, :ptr wchar_t

if 0
if _INTEGRAL_MAX_BITS GE 64
_i64tow		proto __cdecl :qword, :ptr wchar_t, :SINT
_ui64tow	proto __cdecl :sqword, :ptr wchar_t, :SINT
_wtoi64		proto __cdecl :ptr wchar_t
endif
endif
endif ; _WSTDLIB_DEFINED

ifdef _MSVCRT
__getmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__wgetmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__iob_func	proto __cdecl
endif

.pragma list(pop)
endif
