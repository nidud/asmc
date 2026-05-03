ifndef _STDDEF_
define _STDDEF_
ifndef _LIBC_
include libc.inc
endif
ifndef _ERRNO_
include errno.inc
endif

offsetof macro s, m
    exitm<s.&m&>
    endm

__threadid	proto __cdecl
_threadid	equ <__threadid()>
__threadhandle	proto __cdecl

endif
