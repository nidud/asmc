; VFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

vfprintf proc uses rbx file:LPFILE, format:LPSTR, args:ptr

    ldr rcx,file
    mov rbx,_stbuf(rcx)
    _output(file, format, args)
    mov rcx,rbx
    mov rbx,rax
    _ftbuf(ecx, file)
    mov rax,rbx
    ret

vfprintf endp

    end
