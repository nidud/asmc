.pragma list(push, 0)
ifndef _INC_OSCALLS
_INC_OSCALLS equ <>

ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif

include crtdefs.inc

ifdef _WIN32

ifdef NULL
;undef NULL
endif

if defined (_DEBUG) AND defined (_WIN32)

DbgBreakPoint	proto WINAPI
DbgPrint	proto _CDecl :ptr sbyte, :vararg

endif

NOMINMAX equ 1

_WIN32_FUSION equ 0x0100
include windows.inc

ifndef NULL
NULL   equ 0
endif

FTIME			STRUC
time			dw ?	; twosecs:5, minutes:6,	 hours:5
FTIME			ENDS
PFTIME			typedef ptr FTIME

FDATE			STRUC
date			dw ?	; day:5, month:4, year:7
FDATE			ENDS
PFDATE			typedef ptr FDATE

else
.err <ERROR - ONLY WIN32 OR POSIX TARGETS SUPPORTED>
endif
endif
.pragma list(pop)
