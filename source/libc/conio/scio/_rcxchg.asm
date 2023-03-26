; _RCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_rcxchg proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

    mov     rdi,p
    movzx   eax,rc.row
    movzx   ecx,rc.col
    mul     ecx
    mov     ebx,eax
    shl     eax,2
    mov     rsi,malloc(eax)

    .if _rcread(rc, rsi)
        _rcwrite(rc, rdi)
        mov rdx,rsi
        mov ecx,ebx
        rep movsd
        mov rsi,rdx
    .endif
    mov ebx,eax
    free( rsi )
   .return( ebx )

_rcxchg endp

    end
