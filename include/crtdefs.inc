include libc.inc

ifndef _INC_CRTDEFS
define _INC_CRTDEFS

ifdef _CRTBLD
define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
endif

ifndef _WIN32
.err <ERROR: Only Win32 target supported>
endif

include sal.inc

define _CRT_PACKING size_t
.pragma pack(push, _CRT_PACKING)

include vadefs.inc

ifndef _USE_32BIT_TIME_T
ifndef _WIN64
define _USE_32BIT_TIME_T
endif
endif

define _SECURECRT_FILL_BUFFER_PATTERN 0xFE

ifndef _SIZE_T_DEFINED
define _SIZE_T_DEFINED
ifdef _WIN64
size_t typedef qword
else
size_t typedef dword
endif
endif

ifndef _RSIZE_T_DEFINED
define _RSIZE_T_DEFINED
rsize_t typedef size_t
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

ifndef _PTRDIFF_T_DEFINED
define _PTRDIFF_T_DEFINED
ifdef _WIN64
ptrdiff_t typedef sqword
else
ptrdiff_t typedef sdword
endif
endif

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t typedef word
endif

ifndef _WCTYPE_T_DEFINED
define _WCTYPE_T_DEFINED
wint_t typedef word
wctype_t typedef word
endif

ifndef _VA_LIST_DEFINED
define _VA_LIST_DEFINED
va_list typedef ptr sbyte
endif

ifdef _USE_32BIT_TIME_T
ifdef _WIN64
.err <You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64>
endif
endif

ifndef _ERRNO_T_DEFINED
define _ERRNO_T_DEFINED
errno_t typedef sdword
endif
ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef sdword
endif
ifndef _TIME64_T_DEFINED
define _TIME64_T_DEFINED
__time64_t typedef sqword
endif

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
ifdef _WIN64
time_t typedef sqword
else
time_t typedef sdword
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
pthreadmbcinfo		typedef ptr threadmbcinfo
ifndef _locale_t
.template _locale_tstruct
    locinfo		pthreadlocinfo ?
    mbcinfo		pthreadmbcinfo ?
   .ends
   _locale_t		typedef ptr _locale_tstruct
endif

.pragma pack(pop)

ifndef _TRUNCATE
_TRUNCATE equ (-1)
endif

ifndef _CRT_WIDE
__CRT_WIDE macro _String
	exitm<L"&_String&">
	endm
_CRT_WIDE macro _String
	exitm<__CRT_WIDE(_String)>
	endm
endif

@FILECUR2W macro
	local file
	file textequ <L">
%	forc x,<@FileCur>
	    file CatStr file,<x>
	    ifidn <x>,<\>
		file CatStr file,<\>
	    endif
	    endm
	file CatStr file,<">
%	exitm<file>
	endm

__FILEW__ equ <@FILECUR2W()>

ifdef _DEBUG
_invalid_parameter proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :dword, :uintptr_t
else
_invalid_parameter_noinfo macro
	exitm<>
	endm
endif

endif
