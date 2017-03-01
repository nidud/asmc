ifndef __LIBC_INC
 include libc.inc
endif
.xlist
IFDEF __PE__
option	dllimport:<msvcrt>
ENDIF

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

externdef	__argc:dword
externdef	__argv:SIZE_T
externdef	_environ:SIZE_T
externdef	_pgmptr:SIZE_T

abort		PROTO
exit		PROTO :DWORD
atol		PROTO :LPSTR
_atoi64		PROTO :LPSTR
mbtowc		PROTO :LPWSTR, :LPSTR, :SIZE_T
mbstowcs	PROTO :LPWSTR, :LPSTR, :SIZE_T
wctomb		proto :LPSTR, :wchar_t

QSORTCMD_T	TYPEDEF PROTO :PVOID, :PVOID
LPQSORTCMD	TYPEDEF PTR QSORTCMD_T
qsort		PROTO :PVOID, :SIZE_T, :SIZE_T, :LPQSORTCMD

getenv		PROTO :LPSTR
strtod		PROTO :LPSTR, :DWORD
system		PROTO :LPSTR
malloc		proto :SIZE_T
realloc		PROTO :PVOID, :SIZE_T
free		proto :PVOID

xtol		PROTO :LPSTR
_xtoi64		PROTO :LPSTR
mkbstring	PROTO :LPSTR, :QWORD
strtolx		PROTO :LPSTR
searchp		PROTO :LPSTR
getenvp		PROTO :LPSTR
expenviron	PROTO :LPSTR
SaveEnvironment PROTO :LPSTR
ReadEnvironment PROTO :LPSTR
GetEnvironmentTEMP PROTO
GetEnvironmentPATH PROTO
GetEnvironmentSize PROTO :LPSTR

ifndef _WSTDLIB_DEFINED
ifndef _WCHAR_T_DEFINED
wchar_t			typedef WORD
_WCHAR_T_DEFINED	equ 1
endif
ifndef _WCTYPE_T_DEFINED
wint_t			typedef wchar_t
wctype_t		typedef wchar_t
_WCTYPE_T_DEFINED	equ 1
endif

externdef	__wargv:SIZE_T
externdef	_wenviron:SIZE_T
externdef	_wpgmptr:SIZE_T

_itow		proto :SINT, :ptr wchar_t, :SINT
_ltow		proto :SINT, :ptr wchar_t, :SINT
_ultow		proto :DWORD, :ptr wchar_t, :SINT
wcstod		proto :ptr wchar_t, :ptr wchar_t
wcstol		proto :ptr wchar_t, :ptr wchar_t, :SINT
wcstoul		proto :ptr wchar_t, :ptr wchar_t, :SINT
_wgetenv	proto :ptr wchar_t
_wsystem	proto :ptr wchar_t
_wtoi		proto :ptr wchar_t
_wtol		proto :ptr wchar_t
if 0
if _INTEGRAL_MAX_BITS GE 64
_i64tow		proto :qword, :ptr wchar_t, :SINT
_ui64tow	proto :sqword, :ptr wchar_t, :SINT
_wtoi64		proto :ptr wchar_t
endif
endif
_WSTDLIB_DEFINED equ 1
endif

if defined(_MSVCRT) or defined(__PE__)
__getmainargs	proto _CDecl :ptr, :ptr, :ptr, :ptr, :ptr
__wgetmainargs	proto _CDecl :ptr, :ptr, :ptr, :ptr, :ptr
__iob_func	proto _CDecl
endif

.list
