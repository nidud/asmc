; _RCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputsA proc rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, at:WORD, string:LPSTR

    mov     eax,edi
    shr     eax,16
    movzx   eax,al
    mov     r10d,eax
    mul     cl
    movzx   edx,dl
    add     eax,edx
    shl     eax,2
    add     rsi,rax
    sub     r10d,edx

    .for ( rax = r9 : r10d && byte ptr [rax] : r10d--, rax++, rsi+=4 )

        mov edx,r8d
        shl edx,16
        mov dl,[rax]
        .ifz
            mov [rsi],dx
        .else
            mov [rsi],edx
        .endif
    .endf
    sub rax,r9
    ret

_rcputsA endp

    end
