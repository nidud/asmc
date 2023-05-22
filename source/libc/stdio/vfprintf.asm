; VFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

vfprintf proc uses rsi file:LPFILE, format:LPSTR, args:PVOID

    ldr rcx,file
    mov rsi,_stbuf(rcx)
    _output(file, format, args)
    mov rcx,rsi
    mov rsi,rax
    _ftbuf(ecx, file)
    mov rax,rsi
    ret

vfprintf endp

    end
