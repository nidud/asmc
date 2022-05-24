ifndef __STDLIB_INC
define __STDLIB_INC
include libc.inc
.pragma list(push, 0)

ifndef _ERRNO_T_DEFINED
define _ERRNO_T_DEFINED
errno_t typedef sdword
endif

ifndef _INTPTR_T_DEFINED
define _INTPTR_T_DEFINED
ifdef _WIN64
intptr_t typedef sqword
else
intptr_t typedef sdword
endif
endif

ifndef _UINTPTR_T_DEFINED
define _UINTPTR_T_DEFINED
ifdef _WIN64
uintptr_t typedef qword
else
uintptr_t typedef dword
endif
endif

ifndef _THREADLOCALEINFO
define _THREADLOCALEINFO
ifndef LPSHORT
LPINT	typedef ptr sdword
LPSHORT typedef ptr sword
endif
.template locrefcount
    locale		LPSTR ?
    wlocale		LPWSTR ?
    refcount		LPINT ?
    wrefcount		LPINT ?
   .ends
.template threadlocinfo
    refcount		SINT ?
    lc_codepage		UINT ?
    lc_collate_cp	UINT ?
    lc_time_cp		UINT ?
    lc_category		locrefcount 6 dup(<>)
    lc_clike		SINT ?
    mb_cur_max		SINT ?
    lconv_intl_refcount LPINT ?
    lconv_num_refcount	LPINT ?
    lconv_mon_refcount	LPINT ?
    lconvp		PVOID ?
    ctype1_refcount	LPINT ?
    ctype1		LPSHORT ?
    pctype		LPSHORT ?
    pclmap		LPSTR ?
    pcumap		LPSTR ?
    lc_time_curr	ptr __lc_time_data ?
    locale_name		LPWSTR 6 dup(?)
   .ends
    pthreadlocinfo	typedef ptr threadlocinfo
endif

ifndef _locale_t
.template _locale_tstruct
    locinfo		ptr threadlocinfo ?
    mbcinfo		ptr threadmbcinfo ?
   .ends
   _locale_t		typedef ptr _locale_tstruct
endif

ifndef __STDC_WANT_SECURE_LIB__
define __STDC_WANT_SECURE_LIB__ 1
endif

include limits.inc

.pragma comment(lib, libc, msvcrt)

ifndef _ONEXIT_T_DEFINED
define _ONEXIT_T_DEFINED

ifndef _M_CEE_PURE
CALLBACKC(_onexit_t)
else
CALLBACKC(_onexit_t)
_onexit_m_t typedef _onexit_t
endif

ifdef _M_CEE_MIXED
CALLBACKC(_onexit_m_t)
endif

if not __STDC__
onexit_t typedef _onexit_t
endif

endif

ifndef _DIV_T_DEFINED
define _DIV_T_DEFINED
_div_t		struct
quot		int_t ?
rem		int_t ?
_div_t		ends
_ldiv_t		struct
quot		long_t ?
rem		long_t ?
_ldiv_t		ends
_lldiv_t	struct
quot		int64_t ?
rem		int64_t ?
_lldiv_t	ends
endif

ifndef _CRT_DOUBLE_DEC
define _CRT_DOUBLE_DEC

ifndef _LDSUPPORT
.pragma pack(push, 4)
_LDOUBLE struct
    ld	db 10 dup(?)
_LDOUBLE ends
.pragma pack(pop)
_PTR_LD macro x
	exitm<x.ld>
	endm
else
_LDOUBLE typedef real10
_PTR_LD macro x
	exitm<x>
	endm
endif

_CRT_DOUBLE struct
    x	real8 ?
_CRT_DOUBLE ends
_CRT_FLOAT struct
    f	real4 ?
_CRT_FLOAT ends
_LONGDOUBLE struct
    x	real10 ?
_LONGDOUBLE ends

.pragma pack(push,4)
_LDBL12 struct
    ld12 db 12 dup(?)
_LDBL12 ends
.pragma pack(pop)

endif ;; _CRT_DOUBLE_DEC

RAND_MAX equ 0x7fff

;
; Maximum number of bytes in multi-byte character in the current locale
; (also defined in ctype.h).
;
ifndef MB_CUR_MAX
ifdef _CRTBLD
if defined (_DLL) and defined (_M_IX86)
__p___mb_cur_max proto __cdecl
endif
__MB_CUR_MAX macro ptloci
	exitm<ptloci.mb_cur_max>
	endm
endif ; _CRTBLD
if defined(_WIN64) or defined(_MSVCRT)
MB_CUR_MAX equ <___mb_cur_max_func()>
else
MB_CUR_MAX equ <__mb_cur_max>
endif
ifndef _M_CEE_PURE
externdef __mb_cur_max:int_t
else
__p___mb_cur_max proto __cdecl
__mb_cur_max equ <[__p___mb_cur_max()]>
endif
___mb_cur_max_func proto __cdecl
___mb_cur_max_l_func proto __cdecl :_locale_t
endif ; MB_CUR_MAX

_MAX_PATH		equ 260
_MAX_DRIVE		equ 3
_MAX_DIR		equ 256
_MAX_FNAME		equ 256
_MAX_EXT		equ 256

_OUT_TO_DEFAULT		equ 0
_OUT_TO_STDERR		equ 1
_OUT_TO_MSGBOX		equ 2
_REPORT_ERRMODE		equ 3

_WRITE_ABORT_MSG	equ 0x1 ;; debug only, has no effect in release
_CALL_REPORTFAULT	equ 0x2

;;
;; Sizes for buffers used by the getenv/putenv family of functions.
;;
_MAX_ENV		equ 32767

ifndef _M_CEE_PURE
CALLBACKC(_purecall_handler)
_set_purecall_handler	proto __cdecl :_purecall_handler
_get_purecall_handler	proto __cdecl
endif

ifndef _M_CEE_PURE
CALLBACKC(_invalid_parameter_handler, :wstring_t, :wstring_t, :wstring_t, :uint_t, :uintptr_t)
_set_invalid_parameter_handler proto __cdecl :_invalid_parameter_handler
_get_invalid_parameter_handler proto __cdecl
endif

ifndef _CRT_ERRNO_DEFINED
define _CRT_ERRNO_DEFINED
_errno		proto __cdecl
_set_errno	proto __cdecl :int_t
_get_errno	proto __cdecl :ptr int_t
if defined(_WIN64) or defined(_MSVCRT)
errno		equ <errno_t ptr [_errno()]>
else
externdef	errno:errno_t
endif
endif

__doserrno	proto __cdecl
_set_doserrno	proto __cdecl :ulong_t
_get_doserrno	proto __cdecl :ptr ulong_t
__sys_errlist	proto __cdecl
if defined(_WIN64) or defined(_MSVCRT)
_doserrno	equ <errno_t ptr [__doserrno()]>
_sys_errlist	equ <__sys_errlist()>
_sys_nerr	equ <[__sys_nerr()]>
else
externdef	_doserrno:errno_t
externdef	_sys_errlist:array_t
externdef	_sys_nerr:int_t
osmaperr	proto __cdecl
endif
__sys_nerr	proto __cdecl
_dosmaperr	proto __cdecl :ulong_t

if defined (_DLL) and defined (_M_IX86)
__p___argc	proto __cdecl
__p___argv	proto __cdecl
__p___wargv	proto __cdecl
__p__environ	proto __cdecl
__p__wenviron	proto __cdecl
__p__pgmptr	proto __cdecl
__p__wpgmptr	proto __cdecl
ifdef _CRTBLD
__p__fmode	proto __cdecl
endif
endif ;; defined (_DLL) && defined (_M_IX86)

ifndef _M_CEE_PURE
externdef	__argc:int_t
externdef	__argv:array_t
externdef	__wargv:warray_t
else
__p___argc	proto __cdecl
__p___argv	proto __cdecl
__p___wargv	proto __cdecl
__argv		equ <[__p___argv()]>
__argc		equ <[__p___argc()]>
__wargv		equ <[__p___wargv()]>
endif

ifndef _M_CEE_PURE
externdef	_environ:array_t
externdef	_wenviron:warray_t
externdef	_pgmptr:string_t
externdef	_wpgmptr:wstring_t
ifdef _CRTBLD
ifndef _DEFINE_SET_FUNCTION
_DEFINE_SET_FUNCTION macro _FuncName, _Type, _VarName
_FuncName proto watcall _Value:_Type {
    mov _VarName,_Value
    }
exitm<>
endm
endif
_DEFINE_SET_FUNCTION(_set_pgmptr, string_t, _pgmptr)
_DEFINE_SET_FUNCTION(_set_wpgmptr, wstring_t, _wpgmptr)
endif
else
__p__environ	proto __cdecl
__p__wenviron	proto __cdecl
__p__pgmptr	proto __cdecl
__p__wpgmptr	proto __cdecl
_environ	equ <[__p__environ()]>
_wenviron	equ <[__p__wenviron()]>
_pgmptr		equ <[__p__pgmptr()]>
_wpgmptr	equ <[__p__wpgmptr()]>
endif

_get_pgmptr	proto __cdecl :array_t
_get_wpgmptr	proto __cdecl :warray_t

if defined(SPECIAL_CRTEXE) and defined(_CRTBLD)
externdef	_fmode:int_t
else
ifndef _M_CEE_PURE
externdef	_fmode:int_t
else
__p__fmode	proto __cdecl
_fmode		equ <[__p__fmode()]>
endif
endif

_set_fmode	proto __cdecl :int_t
_get_fmode	proto __cdecl :ptr int_t

ifndef _countof
_countof	equ <lengthof>
endif

ifndef _CRT_TERMINATE_DEFINED
define _CRT_TERMINATE_DEFINED
exit		proto __cdecl :int_t
_exit		proto __cdecl :int_t
abort		proto __cdecl
endif

_set_abort_behavior proto __cdecl :int_t, :int_t

abs		proto __cdecl :int_t
labs		proto __cdecl :long_t
llabs		proto __cdecl :int64_t
_abs64		proto __cdecl :int64_t

ifdef _M_CEE
_atexit_m_appdomain proto __cdecl :ptr_t
ifdef _M_CEE_MIXED
_atexit_m	proto __cdecl :ptr_t
else
_atexit_m macro _Function
	exitm<_atexit_m_appdomain(_Function)>
	endm
endif
endif ; _M_CEE

ifdef _M_CEE_PURE
_atexit_m macro _Function
	exitm<_atexit_m_appdomain(_Function)>
	endm
else
atexit		proto __cdecl :ptr
endif

atof		proto __cdecl :string_t
_atof_l		proto __cdecl :string_t, :_locale_t
atoi		proto __cdecl :string_t
_atoi_l		proto __cdecl :string_t, :_locale_t
atol		proto __cdecl :string_t
_atol_l		proto __cdecl :string_t, :_locale_t
atoll		proto __cdecl :string_t
_atoll_l	proto __cdecl :string_t, :_locale_t

ifndef _CRT_ALGO_DEFINED
define _CRT_ALGO_DEFINED
CALLBACKC(LPQSORTCMD, :ptr, :ptr)
if __STDC_WANT_SECURE_LIB__
CALLBACKC(_PtFuncCompare_s, :ptr, :ptr, :ptr)
bsearch_s	proto __cdecl :ptr, :ptr, :size_t, :size_t, :_PtFuncCompare_s, :ptr
endif
CALLBACKC(_PtFuncCompare, :ptr, :ptr)
bsearch		proto __cdecl :ptr, :ptr, :size_t, :size_t, :_PtFuncCompare
if __STDC_WANT_SECURE_LIB__
qsort_s		proto __cdecl :ptr, :size_t, :size_t, :LPQSORTCMD, :ptr
endif
qsort		proto __cdecl :ptr, :size_t, :size_t, :LPQSORTCMD
endif

if 0
_byteswap_ushort proto __cdecl :ushort_t
_byteswap_ulong	 proto __cdecl :ulong_t
_byteswap_uint64 proto __cdecl :uint64_t
;div		 proto __cdecl :int_t, :int_t
endif

getenv		proto __cdecl :string_t
if __STDC_WANT_SECURE_LIB__
getenv_s	proto __cdecl :ptr size_t, :string_t, :size_t, :string_t
endif
_dupenv_s	proto __cdecl :array_t, :ptr size_t, :string_t

_itoa_s		proto __cdecl :int_t, :string_t, :size_t, :int_t
_i64toa_s	proto __cdecl :int64_t, :string_t, :size_t, :int_t
_i64toa		proto __cdecl :int64_t, :string_t, :int_t
_ui64toa_s	proto __cdecl :uint64_t, :string_t, :size_t, :int_t
_ui64toa	proto __cdecl :uint64_t, :string_t, :int_t
_atoi64		proto __cdecl :string_t
_atoi64_l	proto __cdecl :string_t, :_locale_t
_strtoi64	proto __cdecl :string_t, :array_t, :int_t
_strtoi64_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
_strtoui64	proto __cdecl :string_t, :array_t, :int_t
_strtoui64_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
ldiv		proto __cdecl :long_t, :long_t
lldiv		proto __cdecl :int64_t, :int64_t

_ltoa_s		proto __cdecl :long_t, :string_t, :size_t, :int_t

mblen		proto __cdecl :string_t, :size_t
_mblen_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbstrlen	proto __cdecl :string_t
_mbstrlen_l	proto __cdecl :string_t, :_locale_t
_mbstrnlen	proto __cdecl :string_t, :size_t
_mbstrnlen_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbtowc_l	proto __cdecl :wstring_t, :string_t, :size_t, :_locale_t
mbstowcs_s	proto __cdecl :ptr size_t, :wstring_t, :size_t, :string_t, :size_t

_mbstowcs_s_l	proto __cdecl :ptr size_t, :wstring_t, :size_t, :string_t, :size_t, :_locale_t

mbtowc		proto __cdecl :wstring_t, :string_t, :size_t
mbstowcs	proto __cdecl :wstring_t, :string_t, :size_t

rand		proto __cdecl
ifdef _CRT_RAND_S
rand_s		proto __cdecl :ptr uint_t
endif

_set_error_mode proto __cdecl :int_t

srand		proto __cdecl :uint_t
strtod		proto __cdecl :string_t, :array_t
_strtod_l	proto __cdecl :string_t, :array_t, :_locale_t
strtol		proto __cdecl :string_t, :array_t, :int_t
_strtol_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
strtoll		proto __cdecl :string_t, :array_t, :int_t
_strtoll_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
strtoul		proto __cdecl :string_t, :array_t, :int_t
_strtoul_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
strtoull	proto __cdecl :string_t, :array_t, :int_t
_strtoull_l	proto __cdecl :string_t, :array_t, :int_t, :_locale_t
strtold		proto __cdecl :string_t, :array_t
_strtold_l	proto __cdecl :string_t, :array_t, :_locale_t
strtof		proto __cdecl :string_t, :array_t
_strtof_l	proto __cdecl :string_t, :array_t, :_locale_t

ifndef _MSVCRT
_strtold	proto __cdecl :string_t, :string_t
_strtoq		proto __cdecl :ptr, :string_t, :string_t
strtoqd		proto __cdecl :string_t, :string_t
endif

ifndef _CRT_SYSTEM_DEFINED
define _CRT_SYSTEM_DEFINED
system		proto __cdecl :string_t
endif

_ultoa_s	proto __cdecl :ulong_t, :string_t, :size_t, :int_t
wctomb		proto __cdecl :string_t, :wchar_t
_wctomb_l	proto __cdecl :string_t, :wchar_t, :_locale_t
if __STDC_WANT_SECURE_LIB__
wctomb_s	proto __cdecl :ptr int_t, :string_t, :size_t, :wchar_t
endif
_wctomb_s_l	proto __cdecl :ptr int_t, :string_t, :size_t, :wchar_t, :_locale_t
wcstombs_s	proto __cdecl :ptr size_t, :string_t, :size_t, :ptr wchar_t, :size_t
_wcstombs_s_l	proto __cdecl :ptr size_t, :string_t, :size_t, :ptr wchar_t, :size_t, :_locale_t

ifndef _CRT_ALLOCATION_DEFINED
define _CRT_ALLOCATION_DEFINED
calloc		proto __cdecl :size_t, :size_t
free		proto __cdecl :ptr
malloc		proto __cdecl :size_t
realloc		proto __cdecl :ptr, :size_t
_recalloc	proto __cdecl :ptr, :size_t, :size_t
_aligned_free	proto __cdecl :ptr
_aligned_malloc proto __cdecl :size_t, :size_t
_aligned_offset_malloc proto __cdecl :size_t, :size_t, :size_t
_aligned_realloc proto __cdecl :ptr, :size_t, :size_t
_aligned_recalloc proto __cdecl :ptr, :size_t, :size_t, :size_t
_aligned_offset_realloc proto __cdecl :ptr, :size_t, :size_t, :size_t
_aligned_offset_recalloc proto __cdecl :ptr, :size_t, :size_t, :size_t, :size_t
_aligned_msize	proto __cdecl :ptr, :size_t, :size_t
endif

ifndef _WSTDLIB_DEFINED
define _WSTDLIB_DEFINED

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t		typedef word
endif

ifndef _WCTYPE_T_DEFINED
define _WCTYPE_T_DEFINED
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
endif

_itow		proto __cdecl :int_t, :wstring_t, :int_t
_itow_s		proto __cdecl :int_t, :wstring_t, :size_t, :int_t
_ltow		proto __cdecl :int_t, :wstring_t, :int_t
_ltow_s		proto __cdecl :long_t, :wstring_t, :size_t,:int_t
_ultow		proto __cdecl :ulong_t, :warray_t, :int_t
_ultow_s	proto __cdecl :ulong_t, :warray_t, :size_t, :int_t
wcstod		proto __cdecl :wstring_t, :warray_t
_wcstod_l	proto __cdecl :wstring_t, :warray_t, :_locale_t
wcstol		proto __cdecl :wstring_t, :warray_t, :int_t
_wcstol_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t
wcstoll		proto __cdecl :wstring_t, :warray_t, :int_t
_wcstoll_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t
wcstoul		proto __cdecl :wstring_t, :warray_t, :int_t
_wcstoul_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t
wcstoull	proto __cdecl :wstring_t, :warray_t, :int_t
_wcstoull_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t
wcstold		proto __cdecl :wstring_t, :warray_t
_wcstold_l	proto __cdecl :wstring_t, :warray_t, :_locale_t
wcstof		proto __cdecl :wstring_t, :warray_t
_wcstof_l	proto __cdecl :wstring_t, :warray_t, :_locale_t

_wgetenv	proto __cdecl :wstring_t
_wgetenv_s	proto __cdecl :ptr size_t, :wstring_t, :size_t, :wstring_t

_wdupenv_s	proto __cdecl :warray_t, :ptr size_t, :wstring_t

ifndef _CRT_WSYSTEM_DEFINED
define _CRT_WSYSTEM_DEFINED
_wsystem	proto __cdecl :wstring_t
endif

_wtof		proto __cdecl :wstring_t
_wtof_l		proto __cdecl :wstring_t, :_locale_t
_wtoi		proto __cdecl :wstring_t
_wtoi_l		proto __cdecl :wstring_t, :_locale_t
_wtol		proto __cdecl :wstring_t
_wtol_l		proto __cdecl :wstring_t, :_locale_t
_wtoll		proto __cdecl :wstring_t
_wtoll_l	proto __cdecl :wstring_t, :_locale_t

_i64tow_s	proto __cdecl :int64_t, :wstring_t, :size_t, :int_t
_i64tow		proto __cdecl :int64_t, :wstring_t, :int_t
_ui64tow_s	proto __cdecl :uint64_t, :wstring_t, :size_t,:int_t
_ui64tow	proto __cdecl :uint64_t, :wstring_t, :int_t
_wtoi64		proto __cdecl :wstring_t
_wtoi64_l	proto __cdecl :wstring_t, :_locale_t
_wcstoi64	proto __cdecl :wstring_t, :warray_t, :int_t
_wcstoi64_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t
_wcstoui64	proto __cdecl :wstring_t, :warray_t, :int_t
_wcstoui64_l	proto __cdecl :wstring_t, :warray_t, :int_t, :_locale_t

endif ; _WSTDLIB_DEFINED

_CVTBUFSIZE	equ (309+40) ;; # of digits in max. dp value + slop

_fullpath	proto __cdecl :string_t, :string_t, :size_t

_ecvt_s		proto __cdecl :string_t, :size_t, :real8, :int_t, :ptr int_t, :ptr int_t
_ecvt		proto __cdecl :real8, :int_t, :ptr int_t, :ptr int_t
_fcvt_s		proto __cdecl :string_t, :size_t, :real8, :int_t, :ptr int_t, :ptr int_t
_fcvt		proto __cdecl :real8, :int_t, :ptr int_t, :ptr int_t
_gcvt_s		proto __cdecl :string_t, :size_t, :real8, :int_t
_gcvt		proto __cdecl :real8, :int_t, :string_t

_atodbl		proto __cdecl :ptr _CRT_DOUBLE, :string_t
_atoldbl	proto __cdecl :ptr _LDOUBLE, :string_t
_atoflt		proto __cdecl :ptr _CRT_FLOAT, :string_t
_atodbl_l	proto __cdecl :ptr _CRT_DOUBLE, :string_t, :_locale_t
_atoldbl_l	proto __cdecl :ptr _LDOUBLE, :string_t, :_locale_t
_atoflt_l	proto __cdecl :ptr _CRT_FLOAT, :string_t, :_locale_t
;_lrotl		proto __cdecl :ulong_t, :int_t
;_lrotr		proto __cdecl :ulong_t, :int_t
_makepath_s	proto __cdecl :string_t, :size_t, :string_t, :string_t, :string_t, :string_t
_makepath	proto __cdecl :string_t, :string_t, :string_t, :string_t, :string_t

ifdef _M_CEE_PURE
_onexit macro _Function
	exitm<_onexit_m_appdomain(_Function)>
	endm
else
_onexit		proto __cdecl :ptr
endif

ifndef _CRT_PERROR_DEFINED
define _CRT_PERROR_DEFINED
perror		proto __cdecl :string_t
endif

_putenv		proto __cdecl :string_t
_putenv_s	proto __cdecl :string_t, :string_t

if 0 ; use intrin.inc
_rotl		proto __cdecl :int_t, :int_t
_rotl64		proto __cdecl :uint64_t, :int_t
_rotr		proto __cdecl :uint_t, :int_t
_rotr64		proto __cdecl :uint64_t, :int_t
endif

_searchenv_s	proto __cdecl :string_t, :string_t, :string_t, :size_t
_splitpath	proto __cdecl :string_t, :string_t, :string_t, :string_t, :string_t
_splitpath_s	proto __cdecl :string_t, :string_t, :size_t, :string_t, :size_t, :string_t, :size_t, :string_t, :size_t
_swab		proto __cdecl :string_t, :string_t, :int_t

ifndef _WSTDLIBP_DEFINED
define _WSTDLIBP_DEFINED

_wfullpath	proto __cdecl :wstring_t, :wstring_t, :size_t
_wmakepath_s	proto __cdecl :wstring_t, :size_t, :wstring_t, :wstring_t, :wstring_t, :wstring_t
ifndef _CRT_WPERROR_DEFINED
define _CRT_WPERROR_DEFINED
_wperror	proto __cdecl :wstring_t
endif
_wputenv	proto __cdecl :wstring_t
_wputenv_s	proto __cdecl :wstring_t, :wstring_t
_wsearchenv_s	proto __cdecl :wstring_t, :wstring_t, :wstring_t, :size_t

_wsplitpath	proto __cdecl :wstring_t, :wstring_t, :wstring_t, :wstring_t, :wstring_t
_wsplitpath_s	proto __cdecl :wstring_t, :wstring_t, :size_t, :wstring_t, :size_t, :wstring_t, :size_t, :wstring_t, :size_t

endif ;; _WSTDLIBP_DEFINED

;; The Win32 API SetErrorMode, Beep and Sleep should be used instead.
_seterrormode	proto __cdecl :int_t
_beep		proto __cdecl :ulong_t, :ulong_t
_sleep		proto __cdecl :ulong_t

ecvt		proto __cdecl :real8, :int_t, :ptr int_t, :ptr int_t
fcvt		proto __cdecl :real8, :int_t, :ptr int_t, :ptr int_t
gcvt		proto __cdecl :real8, :int_t, :string_t
itoa		proto __cdecl :int_t, :string_t, :int_t
ltoa		proto __cdecl :long_t, :string_t, :int_t

_itoa		proto __cdecl :int_t, :string_t, :int_t
_ltoa		proto __cdecl :long_t, :string_t, :int_t
_ultoa		proto __cdecl :ulong_t, :string_t, :int_t
_i64toa		proto __cdecl :int64_t, :string_t, :int_t
_ui64toa	proto __cdecl :uint64_t, :string_t, :int_t

putenv		proto __cdecl :string_t

swab		proto __cdecl :string_t, :string_t, :int_t
ultoa		proto __cdecl :ulong_t, :string_t, :int_t
onexit		proto __cdecl :onexit_t

;;---

__getmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__wgetmainargs	proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
__iob_func	proto __cdecl

if not defined(_MSVCRT) or defined(_CRTBLD)
setargv		proto __cdecl :ptr int_t, :string_t
setwargv	proto __cdecl :ptr int_t, :ptr wchar_t
_atoi128	proto __cdecl :string_t
qsort4		proto :ptr, :size_t, :LPQSORTCMD
endif
.pragma list(pop)
endif ; __STDLIB_INC

