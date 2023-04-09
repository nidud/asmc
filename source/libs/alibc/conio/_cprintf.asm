; _CPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_cprintf proc format:string_t, argptr:vararg

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    lea rcx,_bufin
    mov o._ptr,rcx
    mov o._base,rcx
    _output(&o, rdi, rax)
    mov rax,o._ptr
    mov byte ptr [rax],0
    _cputs(&_bufin)
    ret

_cprintf endp

    end
