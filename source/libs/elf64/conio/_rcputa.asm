; _RCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputa proc uses rbx w:TRECT, rc:TRECT, p:PCHAR_INFO, a:word

    shr edi,16
    and edi,0xff
    mov ebx,rc
    mov r10,p
    mov r11w,a
    mov r8d,ebx
    shr r8d,16
    mov r9d,r8d
    shr r9d,8

    .for ( : r9b : r9b--, bh++ )

        mov     eax,edi
        mul     bh
        movzx   edx,bl
        add     edx,eax
        shl     edx,2
        add     rdx,r10

        .for ( cl = 0 : cl < r8b : cl++, rdx += 4 )

            mov [rdx+2],r11w
        .endf
    .endf
    ret

_rcputa endp

    end
