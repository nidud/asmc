; VFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_vftprintf proc uses rbx file:LPFILE, format:tstring_t, args:ptr

    mov rbx,_stbuf( ldr(file) )
    _toutput(file, format, args)
    mov rcx,rbx
    mov rbx,rax
    _ftbuf(ecx, file)
    mov rax,rbx
    ret

_vftprintf endp

    end
