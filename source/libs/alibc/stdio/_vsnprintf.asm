; _VSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

_vsnprintf proc string:string_t, count:size_t, format:string_t, vargs:ptr

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,esi
    mov o._ptr,rdi
    mov o._base,rdi
    mov rsi,rdx
    _output(&o, rsi, rcx)
    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

_vsnprintf endp

    end
