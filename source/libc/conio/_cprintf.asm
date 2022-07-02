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
    lea rax,_bufin
    mov o._ptr,rax
    mov o._base,rax
    _output(&o, format, &argptr)
    mov rax,o._ptr
    mov byte ptr [rax],0
    _cputs(&_bufin)
    ret

_cprintf endp

    end
