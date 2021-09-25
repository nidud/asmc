.pragma list(push, 0)
ifndef _INC_STDDEF
define _INC_STDDEF

include crtdefs.inc

ifndef NULL
NULL equ 0
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

offsetof macro s, m
    exitm<s.&m&>
    endm

__threadid	proto __cdecl
_threadid	equ <__threadid()>
__threadhandle	proto __cdecl

endif ;; _INC_STDDEF
.pragma list(pop)
