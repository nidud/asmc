; _RCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_rcxchg proc uses rbx r12 r13 _rc:TRECT, p:PCHAR_INFO

   .new     rc:TRECT = _rc
    mov     r12,p
    movzx   eax,rc.row
    movzx   ecx,rc.col
    mul     ecx
    mov     ebx,eax
    shl     eax,2
    mov     r13,malloc(eax)

    .if _rcread(rc, r13)
        _rcwrite(rc, r12)
        mov rsi,r13
        mov rdi,r12
        mov ecx,ebx
        rep movsd
    .endif
    mov ebx,eax
    free( r13 )
   .return( ebx )

_rcxchg endp

    end
