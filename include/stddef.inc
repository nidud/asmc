ifndef _INC_STDDEF
define _INC_STDDEF
include libc.inc
include errno.inc

offsetof macro s, m
    exitm<s.&m&>
    endm

__threadid	proto __cdecl
_threadid	equ <__threadid()>
__threadhandle	proto __cdecl

endif
