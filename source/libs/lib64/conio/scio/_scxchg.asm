; _SCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scxchg proc uses rsi rdi rbx rc:TRECT, buffer:PCHAR_INFO

    mov     rdi,rdx
    movzx   ebx,rc.col
    movzx   ecx,rc.row
    mul     ebx
    mov     ebx,ecx
    shl     ecx,2
    mov     rsi,malloc(ecx)

    .if _scread(rc, rsi)
        _scwrite(rc, rdi)
        mov rdx,rsi
        mov ecx,ebx
        rep movsd
        mov rsi,rdx
    .endif
    mov ebx,eax
    free(rsi)
   .return(ebx)

_scxchg endp

    end
