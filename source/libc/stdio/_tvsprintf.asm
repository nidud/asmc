; _TVSPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include tchar.inc

    .code

_vstprintf proc string:tstring_t, format:tstring_t, vargs:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rax,format
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, rax, vargs)
    mov rcx,o._ptr
    mov tchar_t PTR [rcx],0
    ret

_vstprintf endp

    end
