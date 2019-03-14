ifndef _INC_STDDEF
_INC_STDDEF equ <>

include crtdefs.inc

ifndef NULL
NULL equ 0
endif

ifndef _CRT_ERRNO_DEFINED
_CRT_ERRNO_DEFINED equ <>
;_errno proto __cdecl
;errno equ <(_errno())>

_set_errno proto __cdecl :int_t
_get_errno proto __cdecl :ptr int_t
endif

offsetof macro s,m
    exitm<s.m>
    endm

__threadid	proto __cdecl
_threadid	equ <__threadid()>
__threadhandle	proto __cdecl

endif ;; _INC_STDDEF
