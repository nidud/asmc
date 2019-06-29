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
    movzx   eax,rc.row
    mul     ebx
    mov     ebx,eax
    shl     eax,2
    mov     rsi,alloca(eax)

    .if _scread(rc, rsi)

        _scwrite(rc, rdi)

        mov ecx,ebx
        rep movsd
    .endif
    ret

_scxchg endp

    end
