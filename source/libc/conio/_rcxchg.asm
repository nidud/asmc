; _RCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_rcxchg proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new b:PCHAR_INFO

    movzx eax,rc.row
    movzx ecx,rc.col
    mul ecx
    mov ebx,eax
    shl eax,2
    mov b,malloc(eax)

    .if _rcread(rc, rax)
        _rcwrite(rc, p)
        mov rdi,p
        mov rsi,b
        mov ecx,ebx
        rep movsd
    .endif
    mov ebx,eax
    free( b )
   .return( ebx )

_rcxchg endp

    end
