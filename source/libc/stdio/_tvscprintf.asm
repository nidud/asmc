; _TVSCPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc
include limits.inc
include tchar.inc

.code

_vsctprintf proc format:tstring_t, argptr:ptr

  local o:_iobuf

    ldr rcx,format
    ldr rdx,argptr

    .if ( rcx == NULL )

        .return( _set_errno( EINVAL ) )
    .endif
    xor eax,eax
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rax
    mov o._base,rax
    _toutput(&o, rcx, rdx)
    ret

_vsctprintf endp

    end
