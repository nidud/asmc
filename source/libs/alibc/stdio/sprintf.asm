; SPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

sprintf proc string:string_t, format:string_t, argptr:vararg

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rdi
    mov o._base,rdi

    _output(addr o, rsi, rax)
    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

sprintf endp

    end
