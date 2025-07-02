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

include vadefs.inc

ifndef _USE_32BIT_TIME_T
ifndef _WIN64
define _USE_32BIT_TIME_T
endif
endif

define _SECURECRT_FILL_BUFFER_PATTERN 0xFE

ifndef _RSIZE_T_DEFINED
define _RSIZE_T_DEFINED
rsize_t typedef size_t
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

include threadlocinfo.inc

ifndef _TRUNCATE
define _TRUNCATE (-1)
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
	exitm<L&__FILE__&>
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
